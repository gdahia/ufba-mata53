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

void solve(const int n, const int m, const int t) {
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

	cout << "Instancia " << t << endl;
	if (colorable)
		cout << "sim" << endl;
	else
		cout << "nao" << endl;
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);	
	int n, m, t = 1;
	while (cin >> n >> m)
		solve(n, m, t++);
}
