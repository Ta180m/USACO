#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[30][30], cost[100001][30] = { 0 }, DP[100001][30];

int main() {
	ifstream cin("cowmbat.in");
	ofstream cout("cowmbat.out");

	int N, M, K;
	string S;
	cin >> N >> M >> K >> S;
	for (int i = 0; i <= 26; ++i) {
		for (int j = 0; j <= 26; ++j) a[i][j] = 1e9;
	}
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) cin >> a[i][j];
	}

	for (int k = 0; k < M; ++k) {
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < M; ++j) a[i][j] = min(a[i][k] + a[k][j], a[i][j]);
		}
	}

	for (int i = 0; i < K; ++i) {
		for (int j = 0; j <= 26; ++j) cost[0][j] += a[S[i] - 'a'][j];
	}
	for (int i = 0; i < N - K; ++i) {
		for (int j = 0; j <= 26; ++j) {
			cost[i + 1][j] = a[S[i + K] - 'a'][j] - a[S[i] - 'a'][j] + cost[i][j];
		}
	}

	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= 26; ++j) DP[i][j] = 1e9;
	}
	DP[0][26] = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= 26; ++j) DP[i + 1][j] = min(a[S[i] - 'a'][j] + DP[i][j], DP[i + 1][j]);
		int best = *min_element(DP[i], DP[i] + 27);
		if (i + K <= N) {
			for (int j = 0; j <= 26; ++j) DP[i + K][j] = min(best + cost[i][j], DP[i + K][j]);
		}
	}
	cout << *min_element(DP[N], DP[N] + 27);
}
