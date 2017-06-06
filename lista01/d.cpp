#include <bits/stdc++.h>
using namespace std;

int p[1123456];
vector<int> adj[1123456];
vector<bool> vis(1123456, false);
vector<int> key, idx;

void dfs(const int v) {
    vis[v] = true;
    key.push_back(p[v]);
    idx.push_back(v);
    for (int u : adj[v])
        if (!vis[u])
            dfs(u);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", p + i);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        key.clear();
        idx.clear();
        dfs(i);
        sort(key.rbegin(), key.rend());
        sort(idx.begin(), idx.end());
        for (int j = 0, len = idx.size(); j < len; j++)
            p[idx[j]] = key[j];
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
    puts("");
}
