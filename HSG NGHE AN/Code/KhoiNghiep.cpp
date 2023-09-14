#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "LOCAL/debug.h"
#else
#define debug(...)
#endif

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > a(n + 1, make_pair(0, 0));
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(1 + a.begin(), a.end());

    priority_queue <int, vector<int>, greater<int> > pq;
    long long ans = 0;
    int cnt = 0;
    for (int i = n; i > 0; --i) {
        pq.push(a[i].second);
        while (!pq.empty() && cnt + (i - 1) < a[i].first) {
            ++cnt;
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("KhoiNghiep.Inp", "r", stdin);
    freopen("KhoiNghiep.Out", "w", stdout);
    int tt = 1;
    while (tt--) {
        solve();
    }

    return 0;
}

