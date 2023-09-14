#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("NAUAN.INP", "r", stdin);
    freopen("NAUAN.OUT", "w", stdout);

    int n;
    cin >> n;
    vector <long long> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1];
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        long long x; cin >> x;
        int ans = lower_bound(a.begin(), a.end(), x) - a.begin();

        cout << ans << ' ';
    }

    return 0;
}