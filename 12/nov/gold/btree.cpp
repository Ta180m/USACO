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

int L[40005];
vi G[40005];
map<int, int> A[40005];
map<int, int, greater<int>> B[40005];

int dfs(int u, int d) {
	int ret = 0;
	L[u] == 1 ? A[u][d] = 1 : B[u][d] = 1;
	for (auto& v : G[u]) {
		ret = max(dfs(v, L[v] + d), ret);
		for (auto& x : A[v]) {
			if (B[u].find(2 * d - L[u] - x.first) != B[u].end()) { // Match left side with corresponding right side
				ret = max(max(x.second, B[u][2 * d - L[u] - x.first]), ret);
			}
		}
		for (auto& x : B[v]) {
			if (A[u].find(2 * d - L[u] - x.first) != A[u].end()) { // Match right side with corresponding left side
				ret = max(max(x.second, A[u][2 * d - L[u] - x.first]), ret);
			}
		}
		for (auto& x : A[v]) A[u][x.first] = max(max(x.first - d, x.second), A[u][x.first]); // Merge A[v] to A[u], adjust max nesting depth accordingly
		for (auto& x : B[v]) B[u][x.first] = max(max(d - x.first, x.second), B[u][x.first]); // Merge B[v] to B[u], adjust max nesting depth accordingly
		A[v].clear(), B[v].clear();
	}
	while (!A[u].empty() && A[u].begin()->first < d) A[u].erase(A[u].begin());
	while (!B[u].empty() && B[u].begin()->first > d) B[u].erase(B[u].begin());
	return ret;
}

int main() {
	init_io("btree");
	int N; cin >> N;
	for (int i = 1; i < N; i++) {
		int p; cin >> p;
		G[--p].push_back(i);
	}
	for (int i = 0; i < N; i++) {
		char c; cin >> c;
		L[i] = (c == '(' ? 1 : -1);
	}
	cout << dfs(0, L[0]);
}
