#include <bits/stdc++.h>
using namespace std;
int dsu[100];
int sz[100];

int find(int v) {
  if (v == dsu[v])
    return v;
  else
    return dsu[v] = find(dsu[v]);
}

int merge(int v, int u) {
  v = find(v);
  u = find(u);
  if (sz[v] > sz[u]) swap(u, v);
  sz[u] += sz[v];
  dsu[v] = u;
}

int main() {
  int n, f, r;
  cin >> n >> f >> r;
  for (int i = 0; i < n; i++) {
    dsu[i] = i;
    sz[i] = 1;
  }
  int m = f + r;
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    edges.emplace_back(w, u, v);
  }
  sort(edges.begin(), edges.begin() + f);
  sort(edges.begin() + f, edges.end());
  int ans = 0;
  for (tuple<int, int, int> e : edges) {
    int u, v, w;
    tie(w, u, v) = e;
    if (find(u) != find(v)) {
      merge(u, v);
      ans += w;
    }
  }
  cout << ans << endl;
}
