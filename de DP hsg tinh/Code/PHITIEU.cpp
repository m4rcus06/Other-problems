#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
long long a[N], dp[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("PHITIEU.INP", "r", stdin);
    freopen("PHITIEU.OUT", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    dp[1] = a[1];
    dp[2] = a[1] + a[2];
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1];
        dp[i] = max(dp[i], dp[i - 2] + a[i]);
        dp[i] = max(dp[i], dp[i - 3] + a[i] + a[i - 1]);
    }

    vector <int> trace;
    for (int i = n; i > 0;) {
        if (i == 1) {
            trace.push_back(i);
            break;
        }
        if (i == 2) {
            trace.push_back(i);
            trace.push_back(i - 1);
            break;
        }
        if (i >= 2 && dp[i] == dp[i - 2] + a[i]) {
            trace.push_back(i);
            i -= 2;
        }
        else if (i >= 3 && dp[i] == dp[i - 3] + a[i] + a[i - 1]) {
            trace.push_back(i);
            trace.push_back(i - 1);
            i -= 3;
        }
        else --i;
    }
    cout << (int)trace.size() << ' ' << dp[n] << '\n';
    for (int i = 0; i < (int)trace.size(); ++i) cout << trace[i] << '\n';
    return 0;
}