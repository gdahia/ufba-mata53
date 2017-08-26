#include <bits/stdc++.h>
using namespace std;

void solve(const int n, const int m) {
  vector<pair<int, int>> adj[n];
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
  }

  int s, t;
  cin >> s >> t;
  s--, t--;

  vector<long long> dist(n, 0x3f3f3f3f);
  dist[s] = 0;

  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                 greater<pair<long long, long long>>>
      pq;
  pq.emplace(0, s);

  while (!pq.empty()) {
    int v, d;
    tie(d, v) = pq.top();
    pq.pop();

    if (dist[v] != d) continue;

    for (pair<int, int>& e : adj[v]) {
      int u = e.first;
      int w = e.second;
      if (dist[u] > d + w) {
        dist[u] = d + w;
        pq.emplace(dist[u], u);
      }
    }
  }

  if (dist[t] == 0x3f3f3f3f)
    cout << -1 << endl;
  else
    cout << dist[t] << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m, n | m) solve(n, m);
}
