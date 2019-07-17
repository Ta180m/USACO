#include <algorithm>
#include <iostream>
using namespace std;

int ans = 0, DP[1 << 20] = { (int)1e9 };
struct cow { int h, w, s; } C[20];

int main() {
	int N, H; cin >> N >> H;
	for (int i = 0; i < N; i++) cin >> C[i].h >> C[i].w >> C[i].s;
	for (int i = 0; i < (1 << N); i++) {
		int h = 0;
		for (int j = 0; j < N; j++) i & 1 << j ? h += C[j].h : DP[i ^ 1 << j] = max(min(C[j].s, DP[i] - C[j].w), DP[i ^ 1 << j]);
		if (h >= H) ans = max(DP[i], ans);
	}
	ans != 0 ? cout << ans << endl : cout << "Mark is too tall" << endl;
}
