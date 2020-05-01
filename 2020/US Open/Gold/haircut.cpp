#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T> class fenwick_tree {
private: vector<T> FT;
public:
	fenwick_tree(int N) { FT.assign(N + 1, 0); }
	void update(int x, T val) { if (x > 0) for (; x < FT.size(); x += x & -x) FT[x] += val; }
	T query(int x) { T ret = 0; if (x > 0) for (; x > 0; x -= x & -x) ret += FT[x]; return ret; }
	T query(int x, int y) { return query(y) - query(x - 1); }
};

ll N, seg[400004] = { 0 }, tmp[400004] = { 0 };
inline ll pull(const ll& l, const ll& r) { return l + r; }
inline void push(int l, int r, int n) {
	seg[n] += (r - l + 1) * tmp[n];
	if (l != r) tmp[n << 1] += tmp[n], tmp[n << 1 | 1] += tmp[n];
	tmp[n] = 0;
}
void update(int a, int b, ll v, int l = 0, int r = -1, int n = 1) {
	if (r == -1) r = N - 1;
	push(l, r, n);
	if (l > b || r < a) return;
	if (l >= a && r <= b) {
		tmp[n] += v;
		push(l, r, n);
	}
	else {
		int m = (l + r) >> 1;
		update(a, b, v, l, m, n << 1), update(a, b, v, m + 1, r, n << 1 | 1);
		seg[n] = pull(seg[n << 1], seg[n << 1 | 1]);
	}
}
ll query(int a, int b, int l = 0, int r = -1, int n = 1) {
	if (r == -1) r = N - 1;
	if (a > b || l > b || r < a) return 0;
	push(l, r, n);
	if (l >= a && r <= b) return seg[n];
	int m = (l + r) >> 1;
	return pull(query(a, b, l, m, n << 1), query(a, b, m + 1, r, n << 1 | 1));
}

int A[100001];

int main() {
	ifstream cin("haircut.in");
	ofstream cout("haircut.out");

	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];

	fenwick_tree<ll> FT(N);
	for (int i = 0; i < N; ++i) {
		update(A[i] + 1, N, FT.query(A[i] + 1, N));
		FT.update(A[i], 1);
	}
	for (int i = 0; i < N; ++i) cout << query(i, i) << '\n';
}
