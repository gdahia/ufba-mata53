#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int mat[n][m];
    int r, c;
    int d[n][m];
    bool vis[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            vis[i][j] = false;
            if (mat[i][j] == 3) {
                r = i;
                c = j;
            }
        }
    queue<pair<int, int>> q;
    q.emplace(r, c);
    d[r][c] = 0;
    vis[r][c] = true;
    int ans;
    while (!q.empty()) {
        tie(r, c) = q.front();
        q.pop();
        if (mat[r][c] == 0) {
            cout << d[r][c] << endl;
            return 0;
        }
        if (r < n - 1 && mat[r + 1][c] != 2 && !vis[r + 1][c]) {
            d[r + 1][c] = d[r][c] + 1;
            vis[r + 1][c] = true;
            q.emplace(r + 1, c);
        }
        if (c < m - 1 && mat[r][c + 1] != 2 && !vis[r][c + 1]) {
            d[r][c + 1] = d[r][c] + 1;
            vis[r][c + 1] = true;
            q.emplace(r, c + 1);
        }
        if (c > 0 && mat[r][c - 1] != 2 && !vis[r][c - 1]) {
            d[r][c - 1] = d[r][c] + 1;
            vis[r][c - 1] = true;
            q.emplace(r, c - 1);
        }
        if (r > 0 && mat[r - 1][c] != 2 && !vis[r - 1][c]) {
            d[r - 1][c] = d[r][c] + 1;
            vis[r - 1][c] = true;
            q.emplace(r - 1, c);
        }
    }
}
