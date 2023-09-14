#include <bits/stdc++.h>
using namespace std;

const int mxN = 1005;
const int inf = 1e9 + 7;

int dx[] = {0, 0, -1, 1};
int dy[] = { -1, 1, 0, 0};

int n, m;
int state[mxN][mxN];
int d[mxN][mxN];

bool ok(int x, int y) {
    return (x > 0 && x <= n && y > 0 && y <= m);
}

void bfs(int x, int y) {
    deque <pair<int, int> > dq;
    d[x][y] = (state[x][y] == 0);
    dq.push_back({x, y});

    while ((int)dq.size() > 0) {
        pair <int, int> u = dq.front(); dq.pop_front();

        for (int i = 0; i < 4; ++i) {
            int v1 = u.first + dx[i];
            int v2 = u.second + dy[i];

            if (ok(v1, v2)) {
                int cost = (state[v1][v2] + d[u.first][u.second]) % 2 + 1;
                if (d[u.first][u.second] + cost < d[v1][v2]) {
                    d[v1][v2] = d[u.first][u.second] + cost;

                    if (cost == 1) dq.push_front({v1, v2});
                    else dq.push_back({v1, v2});
                }
            }
        }
    }
    cout << d[n][m];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("THGT.INP", "r", stdin);
    freopen("THGT.OUT", "w", stdout);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> state[i][j];
            d[i][j] = inf;
        }
    }

    bfs(1, 1);

    return 0;
}