#include <bits/stdc++.h>
using namespace std;

const int mxn = 2e5 + 5;

int n, k;
int a[mxn];
int L1[mxn], L2[mxn];
pair<long long, int> pref[mxn];

int bit[mxn];
void update(int u, int delta) {
    for (; u <= n; u += u & -u) bit[u] += delta;
}

int query(int u) {
    int res = 0;
    for (; u > 0; u -= u & -u) res += bit[u];
    return res;
}

long long countLess(int delta) {
    memset(bit, 0, sizeof bit);

    long long cnt = 0;
    int j = 1;
    for (int i = 1; i <= n; ++i) {
        int pos = min(L1[pref[i].second], L2[pref[i].second]);

        if (pref[i].first <= delta && pos != 0) ++cnt;
        while (j <= n && pref[i].first - pref[j].first <= delta) {
            update(pref[j].second, 1);
            ++j;
        }
        cnt += query(pos - 1);
    }
    return cnt;
}

bool cmp(pair<long long, int> &a, pair<long long, int> &b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    long long sum_odd = 0, sum_even = 0;
    for (int i = 1; i <= n; ++i) {
        L1[i] = L1[i - 1];
        L2[i] = L2[i - 1];

        if (a[i] % 2 == 0) {
            sum_even += a[i];
            L1[i] = i;
        }
        else {
            sum_odd += a[i];
            L2[i] = i;
        }

        pref[i] = make_pair(sum_even - sum_odd, i);
    }
    sort(pref + 1, pref + n + 1, cmp);

    long long ans = countLess(k) - countLess(-1);
    cout << ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tt = 1;
    while (tt--) {
        solve();
    }

    return 0;
}

