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

/*
	a3 <= X*Y <= b3
	case 1: X <= sqrt(b3)
	case 2: Y <= sqrt(b3)
*/

void solve() {
	vector <ll> a(4, 0), b(4, 0);
	cin >> a[1] >> b[1] >> a[2] >> b[2] >> a[3] >> b[3];

	ll res = 0;
	//loop for X
	for (ll x = a[1]; x <= b[1] && x * x <= b[3]; ++x) {
		ll l_bound = ceil(1.0 * a[3] / x), r_bound = b[3] / x;

		ll y1 = max(a[2], l_bound);
		ll y2 = min(b[2], r_bound);

		res += max(0LL, y2 - y1 + 1);
		debug(y1, y2);
	}

	//loop for Y
	for (ll y = a[2]; y <= b[2] && y * y <= b[3]; ++y) {
		ll l_bound = ceil(1.0 * a[3] / y), r_bound = b[3] / y;
		ll lim = sqrt(b[3]) + 1;

		ll x1 = max(a[1], l_bound);
		ll x2 = min(b[1], r_bound);

		debug(x1, x2);
		//avoid counting a pair multiple times (if X and Y both <= b3)
		res += max(0LL, x2 - max(lim, x1) + 1);
	}

	cout << res;
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
