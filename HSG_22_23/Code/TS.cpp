#include <bits/stdc++.h>
using namespace std;

const int mxN = 50005;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("TS.INP", "r", stdin);
    freopen("TS.OUT", "w", stdout);

    int n;
    cin >> n;

    vector <int> cnt(mxN, 0);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i < mxN; ++i) {
        if (cnt[i] > 1) {
            cout << i << ' ' << cnt[i] << '\n';
        }
    }

    return 0;
}