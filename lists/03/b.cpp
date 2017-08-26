#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, long long>> edge;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edge.emplace_back(u, v, w);
  }

  vector<long long> dist(n, 0x3f3f3f3f);
  dist[0] = 0;

  for (int i = 1; i < n; i++)
    for (int j = 0; j < m; j++) {
      int u, v, w;
      tie(u, v, w) = edge[j];

      if (dist[v] > dist[u] + w) dist[v] = dist[u] + w;
    }

  for (int i = 0; i < m; i++) {
    int u, v, w;
    tie(u, v, w) = edge[i];

    if (dist[v] > dist[u] + w) {
      cout << "possible" << endl;
      return;
    }
  }

  cout << "not possible" << endl;
}

int main() {
  int c;
  cin >> c;
  while (c--) solve();
}
