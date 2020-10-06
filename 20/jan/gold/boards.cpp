#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;
constexpr int INF = 1e9;

struct node {
	int val; node* c[2];
	node() { val = -INF; c[0] = c[1] = 0; }
	node* get_c(int i) { return (!c[i] ? c[i] = new node : c[i]); }
	void update(int x, int v, int l = 0, int r = INF) {
		if (l == r) val = max(v, val);
		else {
			int m = (l + r) >> 1;
			x <= m ? get_c(0)->update(x, v, l, m) : get_c(1)->update(x, v, m + 1, r);
			val = max(c[0] ? c[0]->val : -INF, c[1] ? c[1]->val : -INF);
		}
	}
	int query(int a, int b, int l = 0, int r = INF) {
		if (a > r || b < l) return -INF;
		if (a <= l && b >= r) return val;
		int m = (l + r) >> 1;
		return max(c[0] ? c[0]->query(a, b, l, m) : -INF, c[1] ? c[1]->query(a, b, m + 1, r) : -INF);
	}
} seg;

pair<ii, ii> A[100001];

int main() {
	ifstream cin("boards.in");
	ofstream cout("boards.out");

	int N, P;
	cin >> N >> P;
	for (int i = 0; i < P; ++i) cin >> A[i].f.f >> A[i].f.s >> A[i].s.f >> A[i].s.s;
	sort(A, A + P);
	
	seg.update(0, 0);
	set<pair<ii, int>> S;
	for (int i = 0; i < P; ++i) {
		S.emplace(A[i].s, A[i].f.f + A[i].f.s - seg.query(0, A[i].f.s));
		auto it = S.begin();
		while (it != S.end() && it->f.f <= (i < P - 1 ? A[i + 1].f.f : INF)) {
			seg.update(it->f.s, it->f.f + it->f.s - it->s);
			it = S.erase(it);
		}		
	}
	cout << 2 * N - seg.query(0, N);
}
