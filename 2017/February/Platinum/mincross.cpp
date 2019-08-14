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
constexpr auto INF = (ll)1e18;

class fenwick_tree {
private: vector<int> FT;
public:
	fenwick_tree(int N) { FT.assign(N + 1, 0); }
	void update(int x, int val) { for (; x < FT.size(); x += x & -x) FT[x] += val; }
	int query(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += FT[x]; return ret; }
	int query(int x, int y) { return query(y) - (x == 1 ? 0 : query(x - 1)); }
};

int A[100005], B[100005], RA[100005], RB[100005];

int main() {
	ifstream cin("mincross.in");
	ofstream cout("mincross.out");

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) cin >> B[i];
	for (int i = 0; i < N; ++i) RA[A[i]] = i + 1;
	for (int i = 0; i < N; ++i) RB[B[i]] = i + 1;

	fenwick_tree FT(N);
	ll cnt = 0, ans = INF;
	for (int i = 0; i < N; ++i) {
		cnt += FT.query(RA[B[i]], N);
		FT.update(RA[B[i]], 1);
	}
	for (int i = 0; i < N; ++i) {
		cnt += N - 2 * RA[B[i]] + 1;
		ans = min(cnt, ans);
	}
	for (int i = 0; i < N; ++i) {
		cnt += N - 2 * RB[A[i]] + 1;
		ans = min(cnt, ans);
	}
	cout << ans << endl;
}
