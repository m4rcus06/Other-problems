#include <bits/stdc++.h>
using namespace std;

const int mod = 1000003;

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void solve() {
    int n;
    cin >> n;
    vector <vector<char> > a(n + 1, vector<char>(n + 1, '#'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cin >> a[i][j];
    }
    string s;
    cin >> s;
    s = '$' + s;

    vector <vector<int> > dp(n + 1, vector<int>(n + 1, 0));
    vector <vector<bool> > same(n + 1, vector<bool>(n + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            same[i][j] = (a[i][j] == s[i + j - 1]);
            if (same[i][j]) {
                if (same[i - 1][j]) add(dp[i][j], dp[i - 1][j]);
                if (same[i][j - 1]) add(dp[i][j], dp[i][j - 1]);
            }
        }
    }
    cout << dp[n][n];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("FGIRD.INP", "r", stdin);
    freopen("FGIRD.OUT", "w", stdout);

    int tc = 1;
    while (tc--) {
        solve();
    }

    return 0;
}

