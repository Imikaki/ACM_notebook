//source: 

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 4e5 + 10;
int n, sa[N], pos[N], tmp[N], lcp[N], len;

namespace SuffixArray {
	bool cmp(int x, int y) {
		if (pos[x] != pos[y]) return pos[x] < pos[y];
		x += len; y += len;
		return (x <= n && y <= n) ? pos[x] < pos[y] : x > y;
	}

	void buildSA(string s) {
		n = s.size();
		s = '#' + s;

		for (int i = 1; i <= n; ++i) sa[i] = i, pos[i] = s[i];
		tmp[1] = 1;

		for (len = 1; ; len <<= 1) {
			sort (sa + 1, sa + n + 1, cmp);
			for (int i = 1; i < n; ++i) tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i + 1]);
			for (int i = 1; i <= n; ++i) pos[sa[i]] = tmp[i];
			if (tmp[n] == n) break;
		}

		for (int i = 1, k = 0; i <= n; ++i) if (pos[i] != n) {
				for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ++k);
				lcp[pos[i]] = k;
				if (k) --k;
			}
	}
}

struct Vertex {
	Vertex *l, *r;
	int sum = 0;

	Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
	Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
		if (l) sum += l -> sum;
		if (r) sum += r -> sum;
	}
};

struct PersistentSegmentTree {
	Vertex* root[N];
	int at[N];

	Vertex* build(int l, int r) {
		if (l == r) return new Vertex(at[l] = 0);
		int mid = (l + r) >> 1;
		return new Vertex(build(l, mid), build(mid + 1, r));
	}

	int get(Vertex* s, int l, int r, int u, int v) {
		if (l > v || r < u || u > v) return 0;
		if (l >= u && r <= v) return s -> sum;
		int mid = (l + r) >> 1;
		return get(s -> l, l, mid, u, v) + get(s -> r, mid + 1, r, u, v);
	}

	Vertex* up(Vertex* s, int l, int r, int pos, int val) {
		if (l == r) return new Vertex(at[pos] += val);
		int mid = (l + r) >> 1;
		if (pos <= mid) return new Vertex(up(s -> l, l, mid, pos, val), s -> r);
		return new Vertex(s -> l, up(s -> r, mid + 1, r, pos, val));
	}
} it;

struct MergeSortTree {
	vector<int> T[4 * N];

	void build(int s, int l, int r) {
		if (l == r) {
			T[s] = vector<int>(1, sa[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(s << 1, l, mid); build(s << 1 | 1, mid + 1, r);
		T[s].resize(r - l + 1);
		merge(T[s << 1].begin(), T[s << 1].end(), T[s << 1 | 1].begin(), T[s << 1 | 1].end(), T[s].begin());
	}

	int get(int s, int l, int r, int u, int v, int p, int q) {
		if (l > v || r < u || u > v || p > q) return 0;
		if (l >= u && r <= v) return upper_bound(T[s].begin(), T[s].end(), q) - lower_bound(T[s].begin(), T[s].end(), p);
		int mid = (l + r) >> 1;
		return get(s << 1, l, mid, u, v, p, q) + get(s << 1 | 1, mid + 1, r, u, v, p, q);
	}
} mst;

int posS[N], posT[N];

int lg2[N], mi[N][20];

int get(int L, int R) {
	if (L > R) return 1e9;
	int j = lg2[R - L + 1];
	return min(mi[L][j], mi[R - (1 << j) + 1][j]);
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	if (fopen("J.inp", "r")) {
		freopen("J.inp", "r", stdin);
		freopen("J.out", "w", stdout);
	}

	#ifdef LOCAL_MACHINE 
		if (fopen("task.inp", "r")) {
			freopen("task.inp", "r", stdin);
			freopen("task.out", "w", stdout);
		}
	#endif
	
	string s, t; cin >> s >> t;
	string st = s + '#' + t;
	SuffixArray::buildSA(st); // build suffix array + compute LCP (O(nlog^2n))

	for (int i = 2; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;
	for (int i = 1; i < n; ++i) mi[i][0] = lcp[i];
	for (int j = 1; (1 << j) < n; ++j) for (int i = 1; i + (1 << j) - 1 < n; ++i) mi[i][j] = min(mi[i][j - 1], mi[i + (1 << j - 1)][j - 1]);

	//build RMQ on LCP array => LCP(i, j) = min(lcp[pos[i] -> pos[j] - 1])

	int u = s.size(), v = t.size();

	for (int i = 1; i <= n; ++i) {
		if (sa[i] <= u) posS[sa[i]] = i;
		if (sa[i] > u + 1) posT[sa[i] - u - 1] = i;
	}

	// it.root[0] = it.build(1, n);
	// for (int i = 1; i <= v; ++i) it.root[i] = it.up(it.root[i - 1], 1, n, posT[i], 1);
	// cerr << 1.0 * clock() / CLOCKS_PER_SEC << "\n";

	mst.build(1, 1, n);

	int q; cin >> q;
	while (q--) {
		int X, Y, U, V; cin >> X >> Y >> U >> V;

		int px = posS[X], len = Y - X + 1;

		int L, R, lb = px, rb = px;

		L = 1, R = px;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (get(mid, px - 1) >= len) {
				lb = mid;
				R = mid - 1;
			}
			else L = mid + 1;
		}

		L = px, R = n;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (get(px, mid - 1) >= len) {
				rb = mid;
				L = mid + 1;
			}
			else R = mid - 1;
		}

		//binary search for 2 bounds

		// cout << it.get(it.root[max(U - 1, V - len + 1)], 1, n, lb, rb) - it.get(it.root[U - 1], 1, n, lb, rb) << "\n";
		cout << mst.get(1, 1, n, lb, rb, U + u + 1, V - len + 1 + u + 1) << "\n";
	}

	cerr << 1.0 * clock() / CLOCKS_PER_SEC << "\n";
}

// ඞඞඞඞඞ you sus