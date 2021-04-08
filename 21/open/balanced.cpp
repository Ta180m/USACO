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
				
				int d0bb = DP[i][0].query(b,b);
				int d0a1b = DP[i][0].query(a-1,b);
				int d0ba1 = DP[i][0].query(b,a-1);
				int d0a1a1 = DP[i][0].query(a-1,a-1);
				// DP[i][0] query(b,b)-query(a-1,b)-query(b,a-1)+query(a-1,a-1);
				// add(sum, DP[i][0].query(a, b, a, b));
				add(sum, d0bb), add(sum, MOD-d0a1b), add(sum, MOD-d0ba1), add(sum, d0a1a1);
				DP[i+1][0].update(a, b, sum);
				add(ans, sum);

				int d1bn1 = DP[i][1].query(b, N-1);
				int d1a1n1 = DP[i][1].query(a-1, N-1);
				int d1bb1 = DP[i][1].query(b,b-1);
				int d1a1b1 = DP[i][1].query(a-1,b-1);
				int d0bn1 = DP[i][0].query(b,N-1);
				int d0a1n1 = DP[i][0].query(a-1,N-1);
				// DP[i][1] query(b, N-1)-query(a-1,N-1)-query(b,b-1)+query(a-1, b-1)
				// DP[i][0] query(b, N-1)-query(a-1, N-1)-query(b,b)+query(a-1, b)
				// sum = DP[i][1].query(a, b, b, N-1);
				sum = 0; add(sum, d1bn1), add(sum, MOD-d1a1n1), add(sum, MOD-d1bb1), add(sum, d1a1b1);
				// add(sum, DP[i][0].query(a, b, b+1, N-1));
				add(sum, d0bn1), add(sum, MOD-d0a1n1), add(sum, MOD-d0bb), add(sum, d0a1b);
				DP[i+1][1].update(a, b, sum);
				add(ans, sum);

				int d2ab = DP[i][2].query(a, b);
				//int d21b = 0; //DP[i][2].query(-1, b);
				int d2aa1 = DP[i][2].query(a, a-1);
				//int d21a1 = 0; //DP[i][2].query(-1, a-1);
				//int d01b = 0; //DP[i][0].query(-1, b);
				//int d01a1 = 0; //DP[i][0].query(-1, a-1);
				// DP[i][2] query(a,b)-query(-1,b)-query(a, a-1)+query(-1, a-1)
				// DP[i][0] query(a-1, b)-query(-1,b)-query(a-1,a-1)+query(-1,a-1)
				// sum = DP[i][2].query(0, a, a, b);
				sum = 0; add(sum, d2ab); //add(sum, MOD-d21b),
				add(sum, MOD-d2aa1);//, add(sum, d21a1);
				// add(sum, DP[i][0].query(0, a-1, a, b));
				add(sum, d0a1b);//, add(sum, MOD-d01b),
				add(sum, MOD-d0a1a1);//, add(sum, d01a1);
				DP[i+1][2].update(a, b, sum);
				add(ans, sum);

				// int d01n1 = 0;//DP[i][0].query(-1,N-1);
				// int d11n1 = 0;//DP[i][1].query(-1, N-1);
				// int d11b1 = 0;//DP[i][1].query(-1, b-1);
				int d2an1 = DP[i][2].query(a, N-1);
				// int d21n1 = 0;//DP[i][2].query(-1, N-1);
				// DP[i][3] query(a, N-1)-query(-1,N-1)-query(a,b-1)+query(-1, b-1)
				// DP[i][0] query(a-1, N-1)-query(-1,N-1)-query(a-1,b)+query(-1, b)
				// DP[i][1] query(a-1, N-1)-query(-1,N-1)-query(a-1,b-1)+query(-1, b-1)
				// DP[i][2] query(a, N-1)-query(-1,N-1)-query(a,b)+query(-1, b)
				sum = DP[i][3].query(a, N-1); add(sum, MOD-DP[i][3].query(a,b-1));
				// add(sum, DP[i][0].query(0, a-1, b+1, N-1));
				add(sum, d0a1n1);//, add(sum, MOD-d01n1),
				add(sum, MOD-d0a1b);//, add(sum, d01b);
				// add(sum, DP[i][1].query(0, a-1, b, N-1));
				add(sum, d1a1n1);//, add(sum, MOD-d11n1),
				add(sum, MOD-d1a1b1);//, add(sum, d11b1);
				// add(sum, DP[i][2].query(0, a, b+1, N-1));
				add(sum, d2an1);
				//add(sum, MOD-d21n1),
				add(sum, MOD-d2ab);//, add(sum, d21b);
				DP[i+1][3].update(a, b, sum);
				add(ans, sum);
			}
		}
	}
	cout << ans%MOD;
}
