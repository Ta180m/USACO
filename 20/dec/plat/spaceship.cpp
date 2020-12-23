#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 65, MOD = 1e9+7;

ll bs[MX], s[MX], bt[MX], t[MX], L[2*MX], R[2*MX], G[MX][MX], DP[MX][2*MX][2*MX];

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N, K, Q; cin >> N >> K >> Q;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		for (int j = 0; j < N; ++j) G[i][j] = s[j] == '1';
	}
	for (int i = 0; i < Q; ++i)
		cin >> bs[i] >> s[i] >> bt[i] >> t[i], --bs[i], --s[i], --bt[i], --t[i];

	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N+Q; ++k) L[k] = k == j;
			for (int k = 0; k < Q; ++k)
				if (i == bs[k] && j == s[k]) L[N+k] = 1;
			
			for (int k = 0; k < N+Q; ++k)
				for (int l = 0; l < N; ++l)
					if (i && G[l][j]) (L[k] += DP[i-1][k][l]) %= MOD;
			
			for (int k = 0; k < N+Q; ++k) R[k] = k == j;
			for (int k = 0; k < Q; ++k)
				if (i == bt[k] && j == t[k]) R[N+k] = 1;

			for (int k = 0; k < N+Q; ++k)
				for (int l = 0; l < N; ++l)
					if (i && G[j][l]) (R[k] += DP[i-1][l][k]) %= MOD;

			for (int k = 0; k < N+Q; ++k)
				for (int l = 0; l < N+Q; ++l)
					(DP[i][k][l] += L[k]*R[l]) %= MOD;
		}
		memcpy(DP[i+1], DP[i], sizeof DP[i]);
	}

	for (int i = 0; i < Q; ++i) cout << DP[K][N+i][N+i] << '\n';
}
