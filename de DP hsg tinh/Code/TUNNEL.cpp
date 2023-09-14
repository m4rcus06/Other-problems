#include <bits/stdc++.h>
using namespace std;

const int mxN = 105;
const int inf = 1e9 + 7;

struct info {
    int u, v;
    int H, D;
};

int n, m, x, y;
info a[mxN];
int dp[mxN][mxN], dist[mxN][mxN], trace[mxN][mxN], height[mxN][mxN];
bool vis[mxN];
vector <int> adj[mxN];

vector <int> res;

void dfs(int u, int limit) {
    vis[u] = true;
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int v = adj[u][i];
        if (height[u][v] >= limit) {
            dp[u][v] = dist[u][v];
            if (!vis[v]) {
                dfs(v, limit);
            }
        }
    }
}

void setarr() {
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        for (int j = 1; j <= n; ++j) {
            trace[i][j] = i;
            dp[i][j] = inf;
        }
    }
}

bool good(int mid) {
    setarr();
    dfs(x, mid);
    if (!vis[y]) return false;
    res.clear();

    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (dp[u][v] > dp[u][k] + dp[k][v]) {
                    dp[u][v] = dp[u][k] + dp[k][v];
                    trace[u][v] = trace[k][v];
                }
            }
        }
    }



    int u = x, v = y;
    while (v != u) {
        res.push_back(v);
        v = trace[u][v];
    }
    res.push_back(v);
    reverse(res.begin(), res.end());
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("TUNNEL.INP", "r", stdin);
    freopen("TUNNEL.OUT", "w", stdout);

    cin >> n >> x >> y >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, H, D;
        cin >> u >> v >> H >> D;
        a[i] = info {u, v, H, D};

        adj[u].push_back(v);
        adj[v].push_back(u);
        dist[u][v] = dist[v][u] = D;
        height[u][v] = height[v][u] = H;
    }

    int l = 0, r = 10001;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (good(m)) l = m;
        else r = m;
    }
    cout << (int)res.size() << '\n';
    for (int i = 0; i < (int)res.size(); ++i) cout << res[i] << ' ';
    return 0;
}