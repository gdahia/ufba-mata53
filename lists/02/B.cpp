#include <bits/stdc++.h>
using namespace std;

void dfs(int v, vector<pair<int, bool>>* adj, vector<bool>& vis) {
  vis[v] = true;
  for (pair<int, bool> u : adj[v])
    if (!vis[u.first] && u.second) dfs(u.first, adj, vis);
}

void solve(const int n, const int m) {
  map<string, int> dict;
  vector<string> names;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    dict[s] = i;
    names.push_back(s);
  }

  vector<pair<int, bool>> adj[n];
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    string a, b;
    cin >> a >> b;
    adj[dict[b]].emplace_back(dict[a], true);
    edges.emplace_back(dict[a], dict[b]);
  }

  bool some = false;
  for (pair<int, int> e : edges) {
    vector<bool> vis(n, false);
    for (pair<int, bool>& u : adj[e.second])
      if (u.first == e.first) {
        u.second = false;
        break;
      }
    dfs(0, adj, vis);
    for (int i = 0; i < n; i++)
      if (!vis[i]) {
        cout << names[e.first] << " " << names[e.second] << endl;
        some = true;
        break;
      }
    for (pair<int, bool>& u : adj[e.second])
      if (u.first == e.first) {
        u.second = true;
        break;
      }
  }

  if (!some) cout << "Nenhuma" << endl;
  cout << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m, n | m) solve(n, m);
}
