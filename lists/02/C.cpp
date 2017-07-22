#include <bits/stdc++.h>
using namespace std;

bool find_bridge(const int v, vector<int>* adj, vector<int>& vis,
                 vector<int>& low, int& t, const int p) {
  low[v] = vis[v] = t++;
  for (const int u : adj[v])
    if (!vis[u]) {
      if (find_bridge(u, adj, vis, low, t, v)) return true;

      if (low[u] > vis[v]) return true;

      low[v] = min(low[u], low[v]);
    } else if (u != p)
      low[v] = min(low[v], vis[u]);
  return false;
}

void solve(const int n, const int m) {
  vector<int> adj[n];
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> vis(n, 0);
  vector<int> low(n);
  int t = 1;
  if (find_bridge(0, adj, vis, low, t, -1))
    cout << "N" << endl;
  else
    cout << "S" << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m, n | m) solve(n, m);
}
