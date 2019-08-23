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
#define FOR(i, A, B, in) for (int i = (A); i < (B); i += in)
#define REP(i, A, B) for (int i = (A); i < (B); i++)
#define RFOR(i, A, B, in) for (int i = (A) - 1; i >= (B); i -= in)
#define RREP(i, A, B) for (int i = (A) - 1; i >= (B); i--)
#define trav(A, x) for (auto& A : x)
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define mem(A, B) memset(A, (B), sizeof(A))
#define uset unordered_set
#define umap unordered_map
using namespace std;
typedef string str;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii; typedef pair<ll, ll> pl; typedef pair<ld, ld> pd;
typedef vector<int> vi; typedef vector<ll> vl; typedef vector<ld> vd;
typedef vector<ii> vii; typedef vector<pl> vpl; typedef vector<pd> vpd;
constexpr auto INF = (int)1e9;
constexpr auto LINF = (ll)1e18;

vii G[100005];
umap<int, int> A[100005], B[100005];

ll dfs(int u, int p, int s) {
	ll ret = 0;
	for (auto& v : G[u]) { // Traverse children
		if (v.first != p) ret += dfs(v.first, u, s + (v.second ? 1 : -1));
	}
	int m = 0; // Computed largest set to merge small to large
	for (auto& v : G[u]) {
		if (v.first != p && A[v.first].size() + B[v.first].size() > A[m].size() + B[m].size()) m = v.first;
	}
	if (A[m].find(s) != A[m].end()) {
		ret += B[m][s];
		B[u][s] += A[m][s];
		A[m].erase(s);
	}
	if (A[u].size() < A[m].size()) swap(A[u], A[m]);
	if (B[u].size() < B[m].size()) swap(B[u], B[m]);
	for (auto& x : A[m]) A[u][x.first] += x.second;
	for (auto& x : B[m]) B[u][x.first] += x.second;
	// Merge other sets
	for (auto& v : G[u]) {
		if (v.first != p && v.first != m) {
			for (auto& x : A[v.first]) {
				if (B[u].find(2 * s - x.first) != B[u].end()) ret += (ll)x.second * B[u][2 * s - x.first];
			}
			for (auto& x : B[v.first]) {
				if (A[u].find(2 * s - x.first) != A[u].end()) ret += (ll)x.second * A[u][2 * s - x.first];
				if (B[u].find(2 * s - x.first) != B[u].end()) ret += (ll)x.second * B[u][2 * s - x.first];
			}
			if (A[v.first].find(s) != A[v.first].end()) {
				ret += B[v.first][s];
				B[u][s] += A[v.first][s];
				A[v.first].erase(s);
			}
			if (A[u].size() < A[v.first].size()) swap(A[u], A[v.first]);
			if (B[u].size() < B[v.first].size()) swap(B[u], B[v.first]);
			for (auto& x : A[v.first]) A[u][x.first] += x.second; // Merge "A" sets
			for (auto& x : B[v.first]) B[u][x.first] += x.second; // Merge "B" sets
		}
	}
	A[u][s]++;
	return ret;
}

int main() {
	init_io("yinyang");

	int N;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int A, B, t;
		cin >> A >> B >> t;
		G[A].emplace_back(B, t);
		G[B].emplace_back(A, t);
	}
	cout << dfs(1, 0, 0) << endl;
}
