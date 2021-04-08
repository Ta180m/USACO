#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 2e5+5;

int b[MX], l[MX], s[MX];

struct fenwick_tree {
	int FT[MX];
	fenwick_tree() { memset(FT, 0, sizeof FT); }
	inline void update(int x, int v) { if (++x) for (; x < MX; x += x&-x) FT[x] += v; }
	inline int query(int x) { int ret = 0; if (++x) for (; x; x -= x&-x) ret += FT[x]; return ret; }
	inline int query(int x, int y) { return query(y)-query(x-1); }
} range;

struct seg_tree {
	ll seg[4*MX], tmp[4*MX];
	seg_tree() { memset(seg, 0, sizeof seg), memset(tmp, 0, sizeof tmp); }
	inline ll pull(ll a, ll b) { return a+b; }
	inline void push(int l, int r, int n) {
		if (tmp[n]) {
			seg[n] += range.query(l, r) * tmp[n];
			if (l != r) tmp[n<<1] += tmp[n], tmp[n<<1|1] += tmp[n];
			tmp[n] = 0;
		}
	}
	void update(int a, int b, ll v, int l = 0, int r = MX-1, int n = 1) {
		push(l, r, n);
		if (l > r || l > b || r < a) return;
		if (l >= a && r <= b) { tmp[n] += v, push(l, r, n); return; }
		int m = l+r>>1;
		update(a, b, v, l, m, n<<1), update(a, b, v, m+1, r, n<<1|1);
		seg[n] = pull(seg[n<<1], seg[n<<1|1]);
	}
	ll query(int a, int b, int l = 0, int r = MX-1, int n = 1) {
		if (a > b || l > b || r < a) return 0;
		push(l, r, n);
		if (l >= a && r <= b) return seg[n];
		int m = l+r>>1;
		return pull(query(a, b, l, m, n<<1), query(a, b, m+1, r, n<<1|1));
	}
} seg;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);

	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> b[i];

	memset(l, -1, sizeof l), memset(s, -1, sizeof s);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		if (l[b[i]] == -1) {
			seg.update(0, i-2, 1);
		}
		else {
			seg.update(s[b[i]]+1, l[b[i]]-1, -1);
			seg.update(l[b[i]], l[b[i]], -seg.query(l[b[i]], l[b[i]]));
			seg.update(l[b[i]]+1, i-2, 1);
			range.update(l[b[i]], -1);
		}
		range.update(i, 1);
		ans += seg.query(l[b[i]]+1, i-1);
		s[b[i]] = l[b[i]], l[b[i]] = i;
	}
	cout << ans;
}
