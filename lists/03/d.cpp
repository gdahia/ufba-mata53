#include <bits/stdc++.h>
using namespace std;

struct edge {
  int u, v, c, f;
  edge* rev;

  edge(const int u, const int v, const int c, const int f) {
    this->u = u;
    this->v = v;
    this->c = c;
    this->f = f;
    rev = NULL;
  }
};

int cf(const edge& e) {
  if (e.c == 0)
    return e.rev->f;
  else
    return e.c - e.f;
}

vector<edge*> bfs(const int s, vector<vector<edge>>& adj) {
  vector<bool> vis(adj.size(), false);
  vector<edge*> path(adj.size(), NULL);
  vis[s] = true;

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (edge& e : adj[v])
      if (cf(e) > 0 && !vis[e.v]) {
        vis[e.v] = true;
        path[e.v] = &e;
        q.push(e.v);
      }
  }

  return path;
}

void augment(edge& e, const int f) {
  if (e.c == 0)
    e.rev->f -= f;
  else
    e.f += f;
}

void solve() {
  int l, r, speed, constraint;
  cin >> r >> l >> speed >> constraint;

  const int n = l + r + 2;
  vector<vector<edge>> adj(n);
  const int s = 0;
  const int t = n - 1;
  adj[t].reserve(r);
  adj[s].reserve(l);

  vector<pair<int, int>> people;
  for (int i = 1; i <= r; i++) {
    int x, y;
    cin >> x >> y;
    people.emplace_back(x, y);
    adj[i + l].reserve(l + 1);

    adj[i + l].emplace_back(i + l, t, 1, 0);
    adj[t].emplace_back(t, i + l, 0, 0);
    adj[i + l].back().rev = &adj[t].back();
    adj[t].back().rev = &adj[i + l].back();
  }

  for (int i = 1; i <= l; i++) {
    int x, y;
    cin >> x >> y;

    adj[i].reserve(r + 1);
    for (int j = 1; j <= r; j++) {
      int x_, y_;
      std::tie(x_, y_) = people[j - 1];
      if ((abs(x_ - x) + abs(y_ - y)) * 200 <= constraint * speed) {
        adj[i].emplace_back(i, j + l, 1, 0);
        adj[j + l].emplace_back(j + l, i, 0, 0);
        adj[i].back().rev = &adj[j + l].back();
        adj[j + l].back().rev = &adj[i].back();
      }
    }

    adj[s].emplace_back(s, i, 1, 0);
    adj[i].emplace_back(i, s, 0, 0);
    adj[s].back().rev = &adj[i].back();
    adj[i].back().rev = &adj[s].back();
  }

  int ans = 0;
  for (;;) {
    vector<edge*> path = bfs(s, adj);

    // no s-t path
    if (path[t] == NULL) break;

    // find bottleneck
    int b = t;
    int cp = 0x3f3f3f3f;
    while (b != s) {
      const edge& e = *path[b];
      cp = min(cp, cf(e));
      b = e.u;
    }

    // augment path
    b = t;
    while (b != s) {
      edge& e = *path[b];
      augment(e, cp);
      b = e.u;
    }
    ans += cp;
  }

  cout << ans << endl;
}

int main() {
  int k;
  cin >> k;
  while (k--) solve();
}
