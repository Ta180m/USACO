#include <algorithm>
#include <iostream>
using namespace std;

int v[20], p[100005] = { 0 }, DP[1 << 16];

inline int sum(int i, int j) { return p[j + 1] - p[i]; }

int main() {
	int K, N; cin >> K >> N;
	for (int i = 0; i < K; i++) cin >> v[i];
	for (int i = 0; i < N; i++) {
		int c; cin >> c;
		p[i + 1] = c + p[i];
	}

	for (int i = 0; i < (1 << K); i++) if (DP[i] < N) {
		for (int j = 0; j < K; j++) if ((i & 1 << j) == 0) {
			int l = DP[i], h = N;
			while (l + 1 < h) {
				int m = (l + h) / 2;
				sum(DP[i], m) > v[j] ? h = m : l = m;
			}
			DP[i ^ 1 << j] = max(l + 1, DP[i ^ 1 << j]);
		}
	}

	int ans = -1;
	for (int i = 0; i < (1 << K); i++) {
		if (DP[i] == N) {
			int sum = 0;
			for (int j = 0; j < K; j++) if ((i & 1 << j) == 0) sum += v[j];
			ans = max(sum, ans);
		}
	}
	cout << ans << endl;
}
