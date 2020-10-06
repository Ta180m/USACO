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
#define io(s) if (fopen(((string)s+".in").c_str(), "r")) { freopen(((string)s+".in").c_str(), "r", stdin); freopen(((string)s+".out").c_str(), "w", stdout); } ios_base::sync_with_stdio(false); cin.tie(NULL)
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

const int C = 1e5;

int N, cnt = 0, L[100005], R[100005];
ll seg[400005] = { 0 }, tmp[400005] = { 0 };
vector<int> G[100005];
set<ii> S[100005];

void pull(int n) { seg[n] = seg[n << 1] + seg[n << 1 | 1]; }
void push(int l, int r, int n) {
	seg[n] += (r - l + 1) * tmp[n];
	if (l != r) tmp[n << 1] += tmp[n], tmp[n << 1 | 1] += tmp[n];
	tmp[n] = 0;
}
void update(int a, int b, ll v, int l = 1, int r = -1, int n = 1) {
	if (r == -1) r = N;
	push(l, r, n);
	if (l > b || r < a) return;
	if (l >= a && r <= b) {
		tmp[n] += v;
		push(l, r, n);
	}
	else {
		int m = (l + r) >> 1;
		update(a, b, v, l, m, n << 1), update(a, b, v, m + 1, r, n << 1 | 1);
		pull(n);
	}
}
ll query(int a, int b, int l = 1, int r = -1, int n = 1) {
	if (r == -1) r = N;
	if (a > b || l > b || r < a) return 0;
	push(l, r, n);
	if (l >= a && r <= b) return seg[n];
	int m = (l + r) >> 1;
	return query(a, b, l, m, n << 1) + query(a, b, m + 1, r, n << 1 | 1);
}

void dfs(int u, int p) {
	L[u] = ++cnt;
	for (auto& v : G[u]) if (v != p) dfs(v, u);
	R[u] = cnt;
}

int main() {
	io("snowcow");

	int Q;
	cin >> N >> Q;
	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	dfs(1, 0);

	for (int i = 1; i <= C; i++) S[i].emplace(0, 0);

	while (Q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int x, c;
			cin >> x >> c;
			int l = L[x], r = R[x];
			auto it = --S[c].lower_bound(ii(L[x], L[x])); // Get leftmost interval
			while (it != S[c].lower_bound(ii(R[x] + 1, R[x] + 1))) {
				update(max(it->s + 1, L[x]), min(next(it) != S[c].end() ? next(it)->f - 1 : N, R[x]), 1); // Update range between intervals
				if (it->s >= L[x] - 1) {
					l = min(it->f, l);
					r = max(it->s, r);
					it = S[c].erase(it); // Remove covered intervals
				}
				else it++;
			}
			if (it != S[c].end() && it->f <= R[x] + 1) {
				l = min(it->f, l);
				r = max(it->s, r);
				S[c].erase(it);
			}
			S[c].emplace(l, r); // Add interval
		}
		else {
			int x;
			cin >> x;
			cout << query(L[x], R[x]) << '\n';
		}
	}
}
