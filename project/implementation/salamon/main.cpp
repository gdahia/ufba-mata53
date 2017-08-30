#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "minbst.hpp"

int main(const int argc, char** argv) {
  if (argc <= 1)
    throw std::runtime_error("Usage: " + std::string(argv[0]) +
                             " <path to MBV instance> [<path to output>]");

  // open instance file
  std::ifstream input(argv[1]);
  if (!input)
    throw std::runtime_error("Unable to open input file " +
                             std::string(argv[1]));

  // read instance
  int n, m, x;
  input >> n >> m >> x;
  std::vector<int> adj[n];
  for (int i = 0; i < m; i++) {
    int u, v, x;
    input >> u >> v >> x;
    u--, v--;  // make 0 indexed
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  std::vector<std::pair<int, int>> tree = minbst(n, adj);

  // count degrees
  std::vector<int> degree(n, 0);
  for (const std::pair<int, int>& e : tree) {
    degree[e.first]++;
    degree[e.second]++;
  }

  // count branches
  int n_bv = 0;
  for (int i = 0; i < n; i++)
    if (degree[i] >= 3) n_bv++;

  // output answer
  if (argc <= 2) {
    // output to standard output
    std::cout << n_bv << std::endl;
    for (const std::pair<int, int>& e : tree)
      std::cout << e.first + 1 << " " << e.second + 1 << std::endl;
  } else {
    // output to file
    std::ofstream output(argv[3]);
    if (!output)
      throw std::runtime_error("Unable to create output file " +
                               std::string(argv[3]));

    output << n_bv << std::endl;
    for (const std::pair<int, int>& e : tree)
      output << e.first + 1 << " " << e.second + 1 << std::endl;
  }
}
