#include <bits/stdc++.h>
using namespace std;

void solve(const int a, const int v, const int t) {
    vector<int> d(a + 1, 0);
    for (int i = 0; i < v; i++) {
        int x, y;
        cin >> x >> y;
        d[x]++;
        d[y]++;
    }
    int ans = 0;
    for (int i = 1; i <= a; i++)
        if (d[i] > ans)
            ans = d[i];
    cout << "Teste " << t << endl;
    for (int i = 1; i <= a; i++)
        if (d[i] == ans)
            cout << i << " ";
    cout << endl << endl;
}

int main() {
    int a, v, t = 1;
    while (cin >> a >> v, a | v != 0)
        solve(a, v, t++);
}
