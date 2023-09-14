#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "LOCAL/debug.h"
#else
#define debug(...)
#endif

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <typename T1, typename T2> bool minimize(T1 &a, T2 b) {
	if (a > b) {a = b; return true;} return false;
}
template <typename T1, typename T2> bool maximize(T1 &a, T2 b) {
	if (a < b) {a = b; return true;} return false;
}

const int N = 3e5 + 1;

int n, k, x;
ll a[N];
pll bit[N], pre[N];

void update(pll x) {
	int u = x.second;
	for (; u <= n; u += u & -u) {
		bit[u].first += x.first;
		bit[u].second += 1;
	}
}

pll get(ll u) {
	pll ret = {0, 0};
	for (; u > 0; u -= u & -u) {
		ret.first += bit[u].first;
		ret.second += bit[u].second;
	}
	return ret;
}

pll calc(ll mid) {
	for (int i = 1; i <= n; ++i) bit[i] = {0, 0};

	pll cnt = {0, 0};
	for (int l = 1, r = 1; r <= n; ++r) {
		if (pre[r].first >= mid && pre[r].second >= x) {
			cnt.first += pre[r].first;
			cnt.second++;
		}
		while (l <= n && pre[r].first - pre[l].first >= mid) update(pre[l++]);
		pll q = get(pre[r].second - x);

		cnt.first +=  (q.second * pre[r].first) - q.first;
		cnt.second += q.second;
	}
	return cnt;
}


void solve() {
	cin >> n >> k >> x;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int i = 1; i <= n; ++i) {
		pre[i] = {pre[i - 1].first + a[i], i};
	}
	sort(pre + 1, pre + n + 1);

	ll lx = pre[1].first, rx = pre[n].first;
	while (rx - lx > 1) {
		ll mx = (lx + rx) >> 1;

		pll cur_val = calc(mx);
		if (cur_val.second >= k) lx = mx;
		else rx = mx;
	}

	pll ans = calc(lx);
	cout << 1LL * ans.first - (ans.second - k)*lx;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
	freopen("main.in", "r", stdin);
	freopen("main.out", "w", stdout);
#endif

	int tc = 1;
	while (tc--) {
		solve();
	}

	return 0;
}
