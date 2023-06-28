#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "LOCAL/debug.h"
#else
#define debug(...)
#endif

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define first fi
#define second se
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

void solve() {
	string x;
	cin >> x;

	vector <int> num;
	int sum = 0;
	for (int i = 0; i < sz(x); ++i) {
		sum += x[i] - '0';
		num.push_back(x[i] - '0');
	}

	if (sum % 2 != 0) {
		bool found = false;
		for (int i = 0; i < sz(x) - 1; ++i) {
			if (num[i] > 0 && num[i + 1] < 9) {
				found = true;
				num[i]--;
				num[i + 1] += 10;
				break;
			}
		}
		if (!found) {
			cout << -1 << '\n';
			return;
		}
	}


	int dif = 0;
	string x1, x2;
	for (int i = 0; i < sz(x); ++i) {
		int cur = num[i];
		x1.push_back(cur / 2 + '0');
		x2.push_back(cur / 2 + '0');
		cur %= 2;
		if (cur > 0) {
			if (dif >= 0) x2.back()++;
			else x1.back()++;
		}
		dif += x1.back() - x2.back();
	}
	reverse(all(x1));
	reverse(all(x2));
	while (x1.back() == '0') x1.pop_back();
	while (x2.back() == '0') x2.pop_back();
	reverse(all(x1));
	reverse(all(x2));

	cout << x1 << ' ' << x2 << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef LOCAL
	freopen("main.in", "r", stdin);
	freopen("main.out", "w", stdout);
#endif

	int tc = 1;
	cin >> tc;
	while (tc--) {
		solve();
	}

	return 0;
}
