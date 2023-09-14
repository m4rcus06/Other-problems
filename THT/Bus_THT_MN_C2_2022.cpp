#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "LOCAL/debug.h"
#else
#define debug(...) 69420
#endif

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define st first
#define nd second

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e6 + 1;

int n, m, q, a, b;
int tp[N];
int to_left[N], to_right[N];

void solve() {
	cin >> n >> m >> q >> a >> b;
	for (int i = 1; i <= m; ++i) {
		cin >> tp[i];
		to_left[tp[i]] = tp[i];
		to_right[tp[i]] = tp[i];
	}

	for (int i = 1; i <= n; ++i) {
		if (to_left[i] != 0) continue;
		to_left[i] = to_left[i - 1];
	}

	for (int i = n; i > 0; --i) {
		if (to_right[i] != 0 || i == n) continue;
		to_right[i] = to_right[i + 1];
	}

	while (q--) {
		ll x, y;
		cin >> x >> y;
		if (x > y) swap(x, y);
		ll res = (y - x) * a;

		ll l1 = to_left[x], l2 = to_right[x];
		ll r1 = to_left[y], r2 = to_right[y];

		if (l1 && r1) res = min(res, 1LL * abs(x - l1) * a + (r1 - l1) * b + abs(y - r1) * a);
		if (l1 && r2) res = min(res, 1LL * abs(x - l1) * a + (r2 - l1) * b + abs(y - r2) * a);
		if (l2 && r1) res = min(res, 1LL * abs(x - l2) * a + (r1 - l2) * b + abs(y - r1) * a);
		if (l2 && r2) res = min(res, 1LL * abs(x - l2) * a + (r2 - l2) * b + abs(y - r2) * a);

		cout << res << '\n';
	}

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tc = 1;
	while (tc--) {
		solve();
	}

	return 0;
}
