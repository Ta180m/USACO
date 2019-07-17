#include <algorithm>
#include <iostream>
using namespace std;

int h[1 << 20], DP[1 << 20] = { (int)1e9 };

struct cow { int h, w, s; } C[20];

int main() {
	int N, H; cin >> N >> H;
	for (int i = 0; i < N; i++) cin >> C[i].h >> C[i].w >> C[i].s;

	for (int i = 0; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) i & 1 << j ? h[i] += C[j].h : DP[i ^ 1 << j] = max(min(C[j].s, DP[i] - C[j].w), DP[i ^ 1 << j]);
	}

	int ans = 0;
	for (int i = 0; i < (1 << N); i++) if (h[i] >= H) ans = max(DP[i], ans);
	ans != 0 ? cout << ans << endl : cout << "Mark is too tall" << endl;
}
