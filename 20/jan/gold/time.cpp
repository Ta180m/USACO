#include <bits/stdc++.h>
using namespace std;

int m[1001], DP[1001][1001];
vector<int> G[1001];

int main() {
	ifstream cin("time.in");
	ofstream cout("time.out");

	int N, M, C;
	cin >> N >> M >> C;
	for (int u = 1; u <= N; ++u) cin >> m[u];
	while (M--) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
	}

	memset(DP, -1, sizeof DP);
	DP[0][1] = 0;
	for (int i = 0; i < 1000; ++i) {
		for (int u = 1; u <= N; ++u) {
			if (DP[i][u] != -1) {
				for (auto& v : G[u]) {
					DP[i + 1][v] = max(DP[i][u] + m[v], DP[i + 1][v]);
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= 1000; ++i) ans = max(DP[i][1] - C * i * i, ans);
	cout << ans << '\n';
}
