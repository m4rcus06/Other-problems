#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int mxN = 1e5 + 5;

int n;
vector <int> adj[mxN];
int childs[mxN];
vector <int> child_num[mxN];

void dfs(int u, int par) {
    childs[u] = 1;
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) continue;
        dfs(v, u);
        childs[u] += childs[v];
        child_num[u].push_back(childs[v]);
    }
    if (childs[u] != n) child_num[u].push_back(n - childs[u]);
}

bool good(int x) {
    if ((n - 1) % x != 0) return false;
    vector <int> cnt(x + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int valid = 0;
        for (int j = 0; j < (int)child_num[i].size(); ++j) {
            int val = child_num[i][j] % x;
            if (val == 0) continue;

            if (cnt[x - val]) --cnt[x - val], --valid;
            else ++cnt[val], ++valid;
        }
        if (valid != 0) return false;
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    for (int i = 1; i < n; ++i) {
        cout << (good(i) ? 1 : 0);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ROAD.INP", "r", stdin);
    freopen("ROAD.OUT", "w", stdout);

    int tc = 1;
    while (tc--) {
        solve();
    }

    return 0;
}
