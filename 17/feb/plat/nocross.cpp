#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
constexpr auto INF = (int)1e9;
constexpr auto MAXN = 100005;

int N, A[100005], B[100005], R[100005], seg[4 * MAXN] = { 0 };

void update(int x, int v, int l = 0, int r = -1, int n = 1) {
	if (r == -1) r = N - 1;
	if (l == r) seg[n] = max(v, seg[n]);
	else {
		int m = (l + r) >> 1;
		x <= m ? update(x, v, l, m, n << 1) : update(x, v, m + 1, r, n << 1 | 1);
		seg[n] = max(seg[n << 1], seg[n << 1 | 1]);
	}
}

int query(int a, int b, int l = 0, int r = -1, int n = 1) {
	if (r == -1) r = N - 1;
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return seg[n];
	int m = (l + r) >> 1;
	return max(query(a, b, l, m, n << 1), query(a, b, m + 1, r, n << 1 | 1));
}

int main() {
	ifstream cin("nocross.in");
	ofstream cout("nocross.out");

	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i], A[i]--;
	for (int i = 0; i < N; ++i) cin >> B[i], B[i]--;
	for (int i = 0; i < N; ++i) R[B[i]] = i;

	for (int i = 0; i < N; ++i) {
		vii u;
		for (int j = max(A[i] - 4, 0); j < min(A[i] + 5, N); ++j) u.emplace_back(R[j], query(0, R[j] - 1) + 1);
		for (auto q : u) update(q.first, q.second);
	}

	cout << query(0, N - 1) << endl;
}
