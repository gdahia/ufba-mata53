#include <bits/stdc++.h>
using namespace std;

void solve(const int n, const int m) {
  long long d[n][n];
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
    for (int j = i + 1; j < n; j++) d[i][j] = d[j][i] = 0x3f3f3f3f;
  }

  for (int i = 0; i < m; i++) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    u--, v--;
    d[u][v] = min(d[u][v], w);
  }

  int c;
  cin >> c;
  vector<long long> ans(c);
  vector<tuple<int, int, int, int>> query;
  for (int i = 0; i < c; i++) {
    int u, v, k;
    cin >> u >> v >> k;
    u--, v--, k--;
    query.emplace_back(k, u, v, i);
  }

  sort(query.begin(), query.end());
  auto q = query.begin();
  while (q != query.end() && get<0>(*q) < 0) {
    int k, u, v, i;
    tie(k, u, v, i) = *q;
    ans[i] = (d[u][v] != 0x3f3f3f3f ? d[u][v] : -1);
    q++;
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        while (q != query.end()) {
          int qk, qu, qv, qi;
          tie(qk, qu, qv, qi) = *q;
          if (qk == k && qu == i && qv == j) {
            ans[qi] = (d[i][j] != 0x3f3f3f3f ? d[i][j] : -1);
            q++;
          } else
            break;
        }
      }

  for (long long aans : ans) cout << aans << endl;
}

int main() {
  int n, m, t = 1;
  while (cin >> n >> m) {
    cout << "Instancia " << t++ << endl;
    solve(n, m);
    cout << endl;
  }
}
