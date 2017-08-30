#include <cassert>
#include <queue>
#include <utility>
#include <vector>

void mark_dfs(const int v, const std::vector<int>* adj,
              std::vector<bool>& marked, std::queue<int>& s) {
  marked[v] = true;
  s.push(v);

  for (int u : adj[v])
    if (!marked[u]) mark_dfs(u, adj, marked, s);
}

std::vector<std::pair<int, int>> minbst(const int n, const int m,
                                        const std::vector<int>* adj) {
  // initialization
  // initialize empty tree
  std::vector<std::pair<int, int>> tree;
  std::vector<int> H_adj[n];

  // initialize A size
  int A = n;

  // initialize sets A and B
  std::vector<bool> white(n, true);

  // initialize A degree
  std::vector<int> a_degree(n);
  for (int i = 0; i < n; i++) a_degree[i] = adj[i].size();

  // first phase - build a forest
  while (A > 0) {
    // pick v that has most edges to A
    int v = 0;
    for (int i = 0; i < n; i++)
      if (a_degree[i] > a_degree[v]) v = i;

    // update A degrees and add edges to forest H
    for (int u : adj[v])
      // check if u was in A
      if (white[u]) {
        // decrease A degrees of u's neighbors
        for (int w : adj[u])
          if (a_degree[w] > 0) a_degree[w]--;

        // add edge (v, u) to forest
        tree.emplace_back(v, u);
        H_adj[v].push_back(u);
        H_adj[u].push_back(v);

        // add u to B
        white[u] = false;
      }

    // finish updating A degrees
    if (white[v])
      // decrease A degrees of v's neighbors
      for (int u : adj[v])
        if (a_degree[u] > 0) a_degree[u]--;

    // add v to C
    white[v] = false;
    assert(a_degree[v] == 0);
  }

  // second phase - join trees
  std::vector<bool> marked(n, false);
  std::queue<int> s;
  mark_dfs(0, H_adj, marked, s);
  while (!s.empty()) {
    int v = s.front();
    s.pop();

    // check if v has G neighbor not yet in tree
    for (int u : adj[v])
      if (!marked[u]) {
        mark_dfs(0, H_adj, marked, s);
        tree.emplace_back(v, u);
      }
  }

  return tree;
}
