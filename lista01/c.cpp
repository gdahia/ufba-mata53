#include <bits/stdc++.h>
using namespace std;

int dfs(const int v, vector<bool> & vis, vector<int> * adj) {
    vis[v] = true;
    int acc = 1;
    for (int u : adj[v])
        if (!vis[u])
            acc += dfs(u, vis, adj);
    return acc;
}

void solve(const int r, const int c) {
    vector<string> name;
    string a, b;
    for (int i = 0; i < r; i++) {
        cin >> a;
        name.push_back(a);
    }
    sort(name.begin(), name.end());
    vector<int> adj[r];
    for (int i = 0; i < c; i++) {
        cin >> a >> b;
        int ia = lower_bound(name.begin(), name.end(), a) - name.begin();
        int ib = lower_bound(name.begin(), name.end(), b) - name.begin();
        adj[ia].push_back(ib);
        adj[ib].push_back(ia);
    }
    vector<bool> vis(r, false);
    int ans = 0;
    for (int i = 0; i < r; i++)
        if (!vis[i])
            ans = max(ans, dfs(i, vis, adj));
    cout << ans << endl;
}

int main() {
    int r, c;
    while (cin >> r >> c, r | c != 0)
        solve(r, c);
}
