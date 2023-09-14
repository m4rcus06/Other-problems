#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "LOCAL/debug.h"
#else
#define debug(...)
#endif

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define fi first
#define se second
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

const int inf = 1e9 + 7;

struct Node {
	int L, R, sum;
	array <int, 2> minPre, maxPre;
	array <int, 2> minSuf, maxSuf;
	array <int, 3> minSeg, maxSeg;

	Node() {
		L = R = sum = 0;
		minPre = minSuf = {inf, 0};
		maxPre = maxSuf = { -inf, 0};
		minSeg = {inf, 0, 0};
		maxSeg = { -inf, 0, 0};
	}
};

struct ITseg {
	int n;
	vector <Node> tree;
	Node neutral = Node();

	ITseg(int n) {
		this->n = n;
		tree.resize(4 * n + 1, neutral);
	}

	Node compute(int p, int val) {
		Node ret = Node();
		ret.L = ret.R = p;
		ret.sum = val;
		ret.minPre = ret.minSuf = ret.maxPre = ret.maxSuf = {val, p};
		ret.minSeg = ret.maxSeg = {val, p, p};

		return ret;
	}

	Node merge(Node &a, Node &b) {
		Node ret = Node();
		ret.sum = a.sum + b.sum;
		ret.L = a.L;
		ret.R = b.R;

		if (minimize(ret.minPre[0], a.minPre[0])) ret.minPre = a.minPre;
		if (minimize(ret.minPre[0], a.sum + b.minPre[0])) ret.minPre[1] = b.minPre[1];

		if (minimize(ret.minSuf[0], b.minSuf[0])) ret.minSuf = b.minSuf;
		if (minimize(ret.minSuf[0], a.minSuf[0] + b.sum)) ret.minSuf[1] = a.minSuf[1];

		if (minimize(ret.minSeg[0], a.minSeg[0])) ret.minSeg = a.minSeg;
		if (minimize(ret.minSeg[0], b.minSeg[0])) ret.minSeg = b.minSeg;
		if (minimize(ret.minSeg[0], a.minSuf[0] + b.minPre[0])) {
			ret.minSeg[1] = a.minSuf[1];
			ret.minSeg[2] = b.minPre[1];
		}

		if (maximize(ret.maxPre[0], a.maxPre[0])) ret.maxPre = a.maxPre;
		if (maximize(ret.maxPre[0], a.sum + b.maxPre[0])) ret.maxPre[1] = b.maxPre[1];

		if (maximize(ret.maxSuf[0], b.maxSuf[0])) ret.maxSuf = b.maxSuf;
		if (maximize(ret.maxSuf[0], a.maxSuf[0] + b.sum)) ret.maxSuf[1] = a.maxSuf[1];

		if (maximize(ret.maxSeg[0], a.maxSeg[0])) ret.maxSeg = a.maxSeg;
		if (maximize(ret.maxSeg[0], b.maxSeg[0])) ret.maxSeg = b.maxSeg;
		if (maximize(ret.maxSeg[0], a.maxSuf[0] + b.maxPre[0])) {
			ret.maxSeg[1] = a.maxSuf[1];
			ret.maxSeg[2] = b.maxPre[1];
		}

		return ret;
	}

	void build(int id, int l, int r, vector <int> &a) {
		if (l == r) {
			tree[id] = compute(l, a[l]);
			return;
		}

		int m = (l + r) >> 1;
		build(id << 1, l, m, a);
		build(id << 1 | 1, m + 1, r, a);
		tree[id] = merge(tree[id << 1], tree[id << 1 | 1]);
	}

	void build(vector <int> &a) {
		build(1, 1, n, a);
	}

	void update(int id, int l, int r, int i, int k) {
		if (l > i || r < i) return;
		if (l == r) {
			tree[id] = compute(i, k);
			return;
		}

		int m = (l + r) >> 1;
		update(id << 1, l, m, i, k);
		update(id << 1 | 1, m + 1, r, i, k);
		tree[id] = merge(tree[id << 1], tree[id << 1 | 1]);
	}

	void update(int i, int k) {
		update(1, 1, n, i, k);
	}

	Node query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return neutral;
		if (l >= u && r <= v) return tree[id];

		int m = (l + r) >> 1;
		Node x = query(id << 1, l, m, u, v);
		Node y = query(id << 1 | 1, m + 1, r, u, v);
		return merge(x, y);
	}

	Node query(int l, int r) {
		return query(1, 1, n, l, r);
	}
};

struct Itmx {
	/* [0] is Min, [1] is Max, [2] is for Lazy Prop */
	int n;
	vector <array<int, 3>> tree;

	Itmx(int n) {
		this->n = n;
		tree.resize(4 * n, {0, 0, 0});
	}

	void push(int id, int l, int r) {
		int &val = tree[id][2];
		if (val == 0) return;

		for (int i = (id << 1); i <= (id << 1 | 1); ++i) {
			tree[i][0] += val;
			tree[i][1] += val;
			tree[i][2] += val;
		}

		val = 0;
	}

	void update(int id, int l, int r, int u, int v, int k) {
		if (l > v || r < u) return;
		if (l >= u && r <= v) {
			tree[id][0] += k;
			tree[id][1] += k;
			tree[id][2] += k;
			return;
		}

		int m = (l + r) >> 1;
		push(id, l, r);
		update(id << 1, l, m, u, v, k);
		update(id << 1 | 1, m + 1, r, u, v, k);
		tree[id][0] = min(tree[id << 1][0], tree[id << 1 | 1][0]);
		tree[id][1] = max(tree[id << 1][1], tree[id << 1 | 1][1]);
	}

	void update(int l, int r, int k) {
		update(1, 0, n, l, r, k);
	}

	int query_min(int id, int l, int r, int bound, int pos) {
		if (tree[id][0] > bound || r < pos) return -1;
		if (l == r) return l;

		int m = (l + r) >> 1;
		push(id, l, r);
		int res = -1;
		if (tree[id << 1][0] <= bound) res = query_min(id << 1, l, m, bound, pos);
		if (res == -1) res = query_min(id << 1 | 1, m + 1, r, bound, pos);

		return res;
	}

	int query_min(int bound, int pos) {
		return query_min(1, 0, n, bound, pos);
	}

	int query_max(int id, int l, int r, int bound, int pos) {
		if (tree[id][1] < bound || r < pos) return - 1;
		if (l == r) return l;

		int m = (l + r) >> 1;
		push(id, l, r);
		int res = -1;
		if (tree[id << 1][1] >= bound) res = query_max(id << 1, l, m, bound, pos);
		if (res == -1) res = query_max(id << 1 | 1, m + 1, r, bound, pos);

		return res;
	}

	int query_max(int bound, int pos) {
		return query_max(1, 0, n, bound, pos);
	}
};

void solve() {
	int n, q;
	cin >> n >> q;
	vector <int> a(n + 1, 0);
	for (int i = 1; i <= n; ++i) cin >> a[i];

	/*init IT*/
	ITseg st_seg(n);


	Itmx st_max(n); /*<- let P be the prefix sum array of A, this will store maximum/minimum P[i] in range [L, R]*/
	st_max.update(0, 0, 0);
	for (int i = 1; i <= n; ++i) {
		st_max.update(i, n, a[i]);
		st_seg.update(i, a[i]);
	}

	/*tracking for k == 0*/
	set <int> pos;
	for (int i = 2; i <= n; ++i) {
		if (a[i] != a[i - 1]) pos.insert(i);
	}

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int i, v;
			cin >> i >> v;
			int delta = v - a[i];
			if (i > 1 && a[i] != a[i - 1]) pos.erase(pos.find(i));
			if (i < n && a[i] != a[i + 1]) pos.erase(pos.find(i + 1));
			a[i] = v;
			if (i > 1 && a[i] != a[i - 1]) pos.insert(i);
			if (i < n && a[i] != a[i + 1]) pos.insert(i + 1);

			st_seg.update(i, v);
			st_max.update(i, n, delta);
		}
		else {
			int l, r, k;
			cin >> l >> r >> k;
			if (k == 0) {
				auto itr = pos.upper_bound(l);
				if (itr == pos.end() || *itr > r) cout << -1 << '\n';
				else {
					int u = (*itr) - 1;
					int v = *itr;
					cout << u << ' ' << v << '\n';
				}
				continue;
			}
			Node x = st_seg.query(l, r);
			if (k > 0) {
				/* [0]: value, [1,2] = [L, R]*/
				array <int, 3> ans = x.maxSeg;
				if (k > ans[0]) cout << -1 << '\n';
				else {
					int bound = st_seg.query(1, ans[1] - 1).sum + k;
					ans[2] = st_max.query_max(bound, ans[1]);
					cout << ans[1] << ' ' << ans[2] << '\n';
				}
			}
			else {
				array <int, 3> ans = x.minSeg;

				if (k < ans[0]) cout << -1 << '\n';
				else {
					int bound = st_seg.query(1, ans[1] - 1).sum + k;
					debug(bound, st_max.tree[1][0]);
					ans[2] = st_max.query_min(bound, ans[1]);
					cout << ans[1] << ' ' << ans[2] << '\n';
				}
			}
		}
	}
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
