#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 155, MOD = 1e9+7;

inline void add(int & x, int y) { x += y; if (x > MOD) x -= MOD; }

string S[MX];

struct fenwick_tree_2d {
	int FT[MX][MX];
	fenwick_tree_2d() { memset(FT, 0, sizeof FT); }
	inline void update(int x, int y, int v) {
		for (int i = x+1; i < MX; i += i&-i)
            for (int j = y+1; j < MX; j += j&-j) add(FT[i][j], v);
    }
    inline int query(int x, int y) {
        int ret = 0;
        for (int i = x+1; i > 0; i -= i&-i)
            for (int j = y+1; j > 0; j -= j&-j) add(ret, FT[i][j]);
        return ret;
    }
    inline int query(int xl, int xr, int yl, int yr) {
		int ret = query(xr, yr);
		add(ret, MOD-query(xl-1, yr));
		add(ret, MOD-query(xr, yl-1));
		add(ret, query(xl-1, yl-1));
		return ret;
    }
} DP[MX][4];

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);

	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> S[i];

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int a = 0; a < N; ++a) {
			for (int b = a; b < N; ++b) {
				if (S[i][b] != 'G') break;
				
				int sum = 1;
				add(sum, DP[i][0].query(a, b, a, b));
				DP[i+1][0].update(a, b, sum);
				add(ans, sum);

				sum = DP[i][1].query(a, b, b, N-1);
				add(sum, DP[i][0].query(a, b, b+1, N-1));
				DP[i+1][1].update(a, b, sum);
				add(ans, sum);

				sum = DP[i][2].query(0, a, a, b);
				add(sum, DP[i][0].query(0, a-1, a, b));
				DP[i+1][2].update(a, b, sum);
				add(ans, sum);

				sum = DP[i][3].query(0, a, b, N-1);
				add(sum, DP[i][0].query(0, a-1, b+1, N-1));
				add(sum, DP[i][1].query(0, a-1, b, N-1));
				add(sum, DP[i][2].query(0, a, b+1, N-1));
				DP[i+1][3].update(a, b, sum);
				add(ans, sum);
			}
		}
	}
	cout << ans%MOD;
}
