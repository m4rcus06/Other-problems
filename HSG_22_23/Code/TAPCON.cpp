#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("TAPCON.INP", "r", stdin);
    freopen("TAPCON.OUT", "w", stdout);

    int n;
    cin >> n;
    vector <int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector <int> b = a;
    b.erase(unique(b.begin(), b.end()), b.end());

    for (int i = 0; i < (int)b[i].size()) cout << b[i] << ' ';
    return 0;
}