#include <bits/stdc++.h>
using namespace std;

void dfs(const int v, vector<int> * adj, vector<bool> & vis) {
    vis[v] = true;
    for (int u : adj[v])
        if (!vis[u])
            dfs(u, adj, vis);
}

void solve(const int v, const int e) {
    vector<int> adj[v + 1], back_adj[v + 1];
    vector<bool> vis(v + 1, false), back_vis(v + 1, false);
    
    for (int i = 0; i < e; i++) {
        int x, y, p;
        cin >> x >> y >> p;
        adj[x].push_back(y);
        back_adj[y].push_back(x);
        if (p > 1) {
            adj[y].push_back(x);
            back_adj[x].push_back(y);
        }
    }
    
    dfs(1, adj, vis);
    dfs(1, back_adj, back_vis);
    
    bool ans = true;
    for (int i = 1; i <= v; i++)
        if (!vis[i] || !back_vis[i])
            ans = false;
    
    cout << (ans ? 1 : 0) << endl;
}

int main() {
    int n, m;
    while (cin >> n >> m, n | m)
        solve(n, m);
}
