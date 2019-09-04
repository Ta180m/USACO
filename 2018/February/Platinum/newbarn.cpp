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

int S[100005], D[100005], L[100005][16] = { 0 };
ii P[100005];

int lca(int u, int v) {
	if (D[u] > D[v]) swap(u, v);
	for (int i = 15; i >= 0; i--) if (D[v] - (1 << i) >= D[u]) v = L[v][i];
	if (u == v) return u;
	for (int i = 15; i >= 0; i--) if (L[u][i] && L[u][i] != L[v][i]) u = L[u][i], v = L[v][i];
	return L[u][0];
}

inline int dist(int u, int v) { return D[u] + D[v] - 2 * D[lca(u, v)]; }

int main() {
	init_io("newbarn");

	int Q;
	cin >> Q;
	int u = 0, s = 0;
	while (Q--) {
		char c;
		cin >> c;
		if (c == 'B') {
			int p;
			cin >> p;
			u++;
			D[u] = (p != -1 ? D[p] + 1 : 0);
			S[u] = (p != -1 ? S[p] : s++);
			for (int v = p, i = 0; v > 0 && i < 16; v = L[v][i++]) L[u][i] = v;
			if (p != -1) {
				if (dist(u, P[S[u]].first) > dist(P[S[u]].first, P[S[u]].second)) P[S[u]].second = u;
				else if (dist(u, P[S[u]].second) > dist(P[S[u]].first, P[S[u]].second)) P[S[u]].first = u;
			}
			else P[S[u]] = ii(u, u);
		}
		else {
			int k;
			cin >> k;
			cout << max(dist(k, P[S[k]].first), dist(k, P[S[k]].second)) << endl;
		}
	}
}