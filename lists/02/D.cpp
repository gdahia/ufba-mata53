#include <bits/stdc++.h>
using namespace std;

int find_undepended(const vector<vector<int>>& adj) {
  const int n = adj.size();
  vector<bool> vis(n, false);

  int ret = 0;
  bool end = false;
  while (!adj[ret].empty() && !end) {
    vis[ret] = true;
    end = true;
    for (int v : adj[ret])
      if (!vis[v]) {
        ret = v;
        end = false;
        break;
      }
  }

  return ret;
}

void dfs(const int v, const vector<vector<int>>& adj, vector<bool>& vis) {
  vis[v] = true;
  for (int u : adj[v])
    if (!vis[u]) dfs(u, adj, vis);
}

bool reverse_dfs(const int cand, const vector<vector<int>>& adj) {
  const int n = adj.size();
  vector<vector<int>> rev_adj(n);
  for (int i = 0; i < n; i++)
    for (int u : adj[i]) rev_adj[u].push_back(i);

  vector<bool> vis(n, false);
  dfs(cand, rev_adj, vis);

  for (int i = 0; i < n; i++)
    if (!vis[i]) return false;

  return true;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
  }

  int candidate = find_undepended(adj);

  if (!reverse_dfs(candidate, adj))
    cout << 0 << endl;
  else {
    vector<bool> vis(n, false);
    dfs(candidate, adj, vis);
    vector<int> ans;
    for (int i = 0; i < n; i++)
      if (vis[i]) ans.push_back(i + 1);
    cout << ans.size() << endl;
    for (int v : ans) cout << v << " ";
    cout << endl;
  }
}
