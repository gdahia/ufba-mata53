#include <bits/stdc++.h>
using namespace std;
int dsu[1123];
int sz[1123];

int find(int v) {
  if (dsu[v] == v)
    return v;
  else
    return dsu[v] = find(dsu[v]);
}

int merge(int u, int v) {
  v = find(v);
  u = find(u);
  if (sz[u] < sz[v]) swap(u, v);
  sz[u] += sz[v];
  dsu[v] = u;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
  }
  sort(edges.begin(), edges.end());
  for (int i = 0; i < n; i++) {
    dsu[i] = i;
    sz[i] = 1;
  }
  long long ans = 0;
  for (tuple<int, int, int> e : edges) {
    int u, v, w;
    tie(w, v, u) = e;
    if (find(u) != find(v)) {
      merge(u, v);
      ans += w;
    }
  }
  cout << ans << endl;
}
