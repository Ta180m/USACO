#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 2e5+5, B = 300;

int C[MX], L[MX], R[MX], ST[20][MX], ans[MX];
pair<ii, int> P[MX];

inline int query(int i, int j) {
	if (i > j) return MX;
	int k = 31-__builtin_clz(j-i+1);
	return min(ST[k][i], ST[k][j-(1<<k)+1]);
}

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	
	int N, Q; cin >> N >> Q;
	for (int i = 0; i < N; ++i) cin >> C[i];
	for (int i = 0; i < Q; ++i) {
		cin >> P[i].f.f >> P[i].f.s;
		--P[i].f.f, --P[i].f.s, P[i].s = i;
	}

	vector<int> tmp(N+1, -1);
	for (int i = 0; i < N; ++i) L[i] = tmp[C[i]], tmp[C[i]] = i;
	fill(begin(tmp), end(tmp), -1);
	for (int i = N-1; i >= 0; --i) R[i] = tmp[C[i]], tmp[C[i]] = i;
	
	memset(ST, '?', sizeof ST);
	for (int i = 0; i < N; ++i) ST[0][i] = C[i];
	for (int i = 0; i < 18; ++i)
		for (int j = 0; j+(1<<(i+1)) < N; ++j) ST[i+1][j] = min(ST[i][j], ST[i][j+(1<<i)]);

	sort(P, P+Q, [](auto a, auto b) {
		return a.f.f/B == b.f.f/B ? ((a.f.f/B)%2 ? a.f.s > b.f.s : a.f.s < b.f.s) : a.f.f/B < b.f.f/B;
	});
	
	int l = 0, r = -1, cur = 0;
	for (int i = 0; i < Q; ++i) {
		while (l > P[i].f.f) {
			--l;
			if (R[l] == -1 || R[l] > r || query(l+1, R[l]-1) < C[l]) ++cur;
		}
		while (r < P[i].f.s) {
			++r;
			if (L[r] == -1 || L[r] < l || query(L[r]+1, r-1) < C[r]) ++cur;
		}
		while (l < P[i].f.f) {
			if (R[l] == -1 || R[l] > r || query(l+1, R[l]-1) < C[l]) --cur;
			++l;
		}
		while (r > P[i].f.s) {
			if (L[r] == -1 || L[r] < l || query(L[r]+1, r-1) < C[r]) --cur;
			--r;
		}
		ans[P[i].s] = cur;
	}
	for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}
