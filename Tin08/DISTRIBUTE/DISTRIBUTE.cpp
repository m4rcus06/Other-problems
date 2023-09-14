#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 5;
const int mxM = 6e4 + 5;
const long long mod = 1e9 + 7;

int n, m;
long long p[mxM];
vector <int> adj[mxN];

long long cnt[mxN];
bool vis[mxN];
void dfs(int u, int par) {
    cnt[u] = 1;
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i < n ; ++i) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cin >> m;
    vector <long long> p(m + 1, 0);
    for (int i = 1; i <= m; ++i) cin >> p[i];
    sort(1 + p.begin(), p.end());

    dfs(1, 1);
    vector <long long> freq(1, 0LL);
    for (int i = 2; i <= n; ++i) {
        long long prev = cnt[i];
        long long nxt = (n - prev);
        freq.push_back(1LL * prev * nxt);
    }
    sort(1 + freq.begin(), freq.end());

    long long res = 0;
    if (m < n - 1) {
        reverse(1 + freq.begin(), freq.end());
        reverse(1 + p.begin(), p.end());

        for (int i = 1; i <= m; ++i) {
            long long x = freq[i] % mod;
            res = (res + p[i] * x) % mod;
        }
        for (int i = m + 1; i < n; ++i) {
            res = (res + freq[i]) % mod;
        }
    }
    else {
        for (int i = 1; i < n - 1; ++i) {
            res = (res + freq[i] % mod * p[i]) % mod;
        }
        long long x = freq.back();
        for (int i = n - 1; i <= m; ++i) {
            x = x * p[i] % mod;
        }
        res = (res + x) % mod;
    }
    cout << res;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("DISTRIBUTE.INP", "r", stdin);
    freopen("DISTRIBUTE.OUT", "w", stdout);

    int tc = 1;
    while (tc--) {
        solve();
    }

    return 0;
}

