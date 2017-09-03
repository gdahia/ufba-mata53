#include <bits/stdc++.h>
using namespace std;

struct edge {
  int u, v, c, f;

  edge(const int u, const int v, const int c, const int f) {
    this->u = u;
    this->v = v;
    this->c = c;
    this->f = f;
  }
};

vector<edge> edges;

int cf(const int e) {
  if (edges[e].c == 0)
    return edges[e - 1].f;
  else
    return edges[e].c - edges[e].f;
}

vector<int> bfs(const int s, const vector<vector<int>>& adj) {
  vector<bool> vis(adj.size(), false);
  vector<int> path(adj.size(), -1);
  vis[s] = true;

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (const int e : adj[v]) {
      if (cf(e) > 0 && !vis[edges[e].v]) {
        vis[edges[e].v] = true;
        path[edges[e].v] = e;
        q.push(edges[e].v);
      }
    }
  }

  return path;
}

void augment(const int e, const int f) {
  if (edges[e].c == 0)
    edges[e - 1].f -= f;
  else
    edges[e].f += f;
}

void solve(const int l, const int r, const int m) {
  edges.clear();
  const int n = l + r + 2;
  vector<vector<int>> adj(n);
  const int s = 0;
  const int t = n - 1;

  for (int i = 1; i <= l; i++) {
    int c;
    cin >> c;
    edges.emplace_back(s, i, c, 0);
    adj[s].push_back(edges.size() - 1);
    edges.emplace_back(i, s, 0, 0);
    adj[i].push_back(edges.size() - 1);
  }

  for (int i = 1; i <= r; i++) {
    edges.emplace_back(i + l, t, 1, 0);
    adj[i + l].push_back(edges.size() - 1);
    edges.emplace_back(t, i + l, 0, 0);
    adj[t].push_back(edges.size() - 1);
  }

  for (int i = 0; i < m; i++) {
    int v, u;
    cin >> v >> u;
    edges.emplace_back(v, u + l, 1, 0);
    adj[v].push_back(edges.size() - 1);
    edges.emplace_back(u + l, v, 0, 0);
    adj[u + l].push_back(edges.size() - 1);
  }

  int ans = 0;
  for (;;) {
    vector<int> path = bfs(s, adj);

    // no s-t path
    if (path[t] == -1) break;

    // find bottleneck
    int b = t;
    int cp = 0x3f3f3f3f;
    while (b != s) {
      const int e = path[b];
      cp = min(cp, cf(e));
      b = edges[e].u;
    }

    // augment path
    b = t;
    while (b != s) {
      const int e = path[b];
      augment(e, cp);
      b = edges[e].u;
    }
    ans += cp;
  }

  cout << ans << endl;
}

int main() {
  int l, r, m;
  int ndt = 1;
  while (cin >> l >> r >> m) {
    cout << "Instancia " << ndt++ << endl;
    solve(l, r, m);
    cout << endl;
  }
}
