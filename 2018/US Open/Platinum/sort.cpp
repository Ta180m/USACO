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
#define init_io(pname) ifstream cin((string)pname+".in"); ofstream cout((string)pname+".out"); ios_base::sync_with_stdio(false); cin.tie(NULL)
#define FOR(i, a, b, in) for (int i = (a); i < (b); i += in)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RFOR(i, a, b, in) for (int i = (a) - 1; i >= (b); i -= in)
#define RREP(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define trav(a, x) for (auto& a : x)
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define mem(a, b) memset(a, (b), sizeof(a))
using namespace std;
typedef string str;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii; typedef pair<ll, ll> pl; typedef pair<ld, ld> pd;
typedef vector<int> vi; typedef vector<ll> vl; typedef vector<ld> vd;
typedef vector<ii> vii; typedef vector<pl> vpl; typedef vector<pd> vpd;
constexpr auto INF = (int)1e9;
constexpr auto LINF = (ll)1e18;

template<typename T> class fenwick_tree {
private: vector<T> FT;
public:
	fenwick_tree(int N) { FT.assign(N + 1, 0); }
	void clear() { FT.assign(FT.size(), 0); }
	void update(int x, T val) { if (x > 0) for (; x < FT.size(); x += x & -x) FT[x] += val; }
	T query(int x) { T ret = 0; if (x > 0) for (; x > 0; x -= x & -x) ret += FT[x]; return ret; }
	T query(int x, int y) { return query(y) - (x == 1 ? 0 : query(x - 1)); }
};

template< typename T > class seg_tree {
private:
	int N;
	vector<T> seg, tmp;
public:
	seg_tree(int size) {
		N = size;
		seg.resize(4 * N, 0);
		tmp.resize(4 * N, 0);
	}
	seg_tree(int size, T A[]) {
		N = size;
		seg.resize(4 * N);
		tmp.resize(4 * N);
		build(A);
	}
	seg_tree(vector<T>& A) {
		N = A.size();
		seg.resize(4 * N);
		tmp.resize(4 * N);
		build(A);
	}
	void clear() { seg.assign(4 * N, 0); }
	void pull(int n) { seg[n] = max(seg[n << 1], seg[n << 1 | 1]); }
	void push(int l, int r, int n) {
		seg[n] += tmp[n];
		if (l != r) tmp[n << 1] += tmp[n], tmp[n << 1 | 1] += tmp[n];
		tmp[n] = 0;
	}
	void build(T A[], int l = 0, int r = -1, int n = 1) {
		if (r == -1) r = N - 1;
		if (l == r) seg[n] = A[l];
		else {
			int m = (l + r) >> 1;
			build(A, l, m, n << 1), build(A, m + 1, r, n << 1 | 1);
			pull(n);
		}
	}
	void build(vector<T>& A, int l = 0, int r = -1, int n = 1) {
		if (r == -1) r = N - 1;
		if (l == r) seg[n] = A[l];
		else {
			int m = (l + r) >> 1;
			build(A, l, m, n << 1);
			build(A, m + 1, r, n << 1 | 1);
			pull(n);
		}
	}
	void update(int x, T v, int l = 0, int r = -1, int n = 1) {
		if (r == -1) r = N - 1;
		if (l == r) seg[n] += v;
		else {
			int m = (l + r) >> 1;
			x <= m ? update(x, v, l, m, n << 1) : update(x, v, m + 1, r, n << 1 | 1);
			pull(n);
		}
	}
	void update_range(int a, int b, T v, int l = 0, int r = -1, int n = 1) {
		if (r == -1) r = N - 1;
		push(n, l, r);
		if (l > b || r < a) return;
		if (l >= a && r <= b) {
			tmp[n] = v;
			push(n, l, r);
		}
		else {
			int m = (l + r) >> 1;
			update_range(a, b, v, l, m, n << 1), update_range(a, b, v, m + 1, r, n << 1 | 1);
			pull(n);
		}
	}
	T query(int a, int b, int l = 0, int r = -1, int n = 1) {
		if (r == -1) r = N - 1;
		if (l > b || r < a) return 0;
		push(n, l, r);
		if (l >= a && r <= b) return seg[n];
		int m = (l + r) >> 1;
		return max(query(a, b, l, m, n << 1), query(a, b, m + 1, r, n << 1 | 1));
	}
};

int A[100005], C[100005] = { 0 };

int main() {
	init_io("sort");

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) cin >> A[i];
	vector<ii> tmp;
	for (int i = 0; i < N; i++) tmp.emplace_back(A[i], i);
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < N; i++) A[tmp[i].second] = i;

	ll ans = 0;
	fenwick_tree<int> FT(N);
	seg_tree<int> seg(N);
	for (int i = 0; i < N; i++) {
		ans += FT.query(A[i], N - 1);
		FT.update(A[i], 1);
	}
	for (int i = 0; i < N; i++) seg.update(A[i], i);
	for (int i = 0; i < N; i++) {
		int q = seg.query(0, A[i]);
		if (i != q) C[i]++, C[q]--, ans++;
	}
	FT.clear();
	for (int i = N - 1; i >= 0; i--) {
		ans += (ll)C[i] * FT.query(A[i], N - 1);
		FT.update(A[i], 1);
	}
	cout << (ans ? ans : N) << endl;
}
