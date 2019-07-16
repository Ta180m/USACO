#include <algorithm>
#include <iostream>
using namespace std;
constexpr auto INF = (int)1e9;

int N, C, H, A[105], B[105], DP[105];

int main() {
	cin >> N >> C;
	for (int i = 0; i < N; i++) { cin >> H;
		for (int j = 0; j <= 100; j++) DP[j] = (j < H ? INF : (j - H) * (j - H) + (i > 0) * min(A[j] + C * j, B[j] - C * j));
		for (int j = 0; j <= 100; j++) A[j] = min(DP[j] - C * j, (j <= 0 ? INF : A[j - 1]));
		for (int j = 100; j >= 0; j--) B[j] = min(DP[j] + C * j, (j >= 100 ? INF : B[j + 1]));
	}
	cout << *min_element(DP, DP + 100) << endl;
}
