#include <bits/stdc++.h>
using namespace std;

void toposort(vector<int>* adj, vector<int>& rev_adj) {
  const int n = rev_adj.size();

  priority_queue<int, vector<int>, greater<int>> q;

  for (int i = 0; i < n; i++)
    if (!rev_adj[i]) q.push(i);

  vector<int> ans;

  while (!q.empty()) {
    int v = q.top();
    q.pop();

    ans.push_back(v);

    for (int u : adj[v]) {
      rev_adj[u]--;
      if (!rev_adj[u]) q.push(u);
    }
  }

  if (ans.size() != n)
    cout << "*" << endl;
  else
    for (int i : ans) cout << i << endl;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> rev_adj(n, 0);
  vector<int> adj[n];

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    rev_adj[v]++;
    adj[u].push_back(v);
  }

  toposort(adj, rev_adj);
}
