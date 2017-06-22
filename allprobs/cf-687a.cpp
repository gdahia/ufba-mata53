#include <bits/stdc++.h>
using namespace std;

bool dfs(const int v, vector<int> * adj, vector<int> & vcolor, const int color) {
	vcolor[v] = color;
	bool colorable = true;
	for (int u : adj[v])
		if (vcolor[u] == color || !(vcolor[u] || dfs(u, adj, vcolor, -color))) {
			colorable = false;
			break;
		}
	return colorable;
}

void solve(const int n, const int m) {
	vector<int> adj[n + 1];
	vector<int> color(n + 1, 0);

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	bool colorable = true;
	for (int i = 1; i <= n; i++)
		if (!color[i] && !dfs(i, adj, color, 1)) {
			colorable = false;
			break;
		}

	if (!colorable)
		cout << -1 << endl;
	else {
		for (int i = -1; i <= 1; i += 2) {
			int cmp_size = 0;
			for (int v = 1; v <= n; v++)
				cmp_size += (color[v] == i);
			cout << cmp_size << endl;
			for (int v = 1; v <= n; v++)
				if (color[v] == i)
					cout << v << " ";
			cout << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);	
	int n, m;
	cin >> n >> m;
	solve(n, m);
}
