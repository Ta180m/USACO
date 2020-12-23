#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
const int MX = 3005, MOD = 1e9+7;


ll s[MX], t[MX], DP[2][MX][2];


int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> s[i];
	for (int i = 0; i < N; ++i) cin >> t[i];

	vector<ii> vc;
	for (int i = 0; i < N; ++i) vc.emplace_back(s[i], 0);
	for (int i = 0; i < N; ++i) vc.emplace_back(t[i], 1);
	sort(begin(vc), end(vc));

	DP[0][0][0] = 1;
	for (int i = 0; i < 2*N; ++i) {
		if (vc[i].s == 0) {
			for (int j = 0; j <= N; ++j) {
				(DP[1][j][1] += DP[0][j][0]) %= MOD;
				(DP[1][j+1][0] += DP[0][j][0]) %= MOD;
				(DP[1][j][1] += DP[0][j][1]) %= MOD;
				(DP[1][j+1][1] += DP[0][j][1]) %= MOD;
			}
		}
		else {
			for (int j = 0; j <= N; ++j) {
				(DP[1][j][0] += DP[0][j][0]) %= MOD;
				if (j) (DP[1][j-1][0] += j*DP[0][j][0]) %= MOD;
				if (j) (DP[1][j-1][1] += j*DP[0][j][1]) %= MOD;
			}
		}
		memcpy(DP[0], DP[1], sizeof DP[1]);
		memset(DP[1], 0, sizeof DP[1]);
	}
	cout << (DP[0][0][0]+DP[0][0][1])%MOD;
}
