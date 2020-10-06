#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;

int N, M, T[100001], d[100001] = { 0 }, L[100001][20];
vector<int> G[100001];
bitset<100001> ans;
pair<ii, int> q[100001];
unordered_set<int> x[100001], y[100001];

void dfs(int u, int p) {
	d[u] = d[p] + 1;
	L[u][0] = p;
	for (int i = 0; i < 18 && L[u][i]; i++) L[u][i + 1] = L[L[u][i]][i];
	for (auto& v : G[u]) if (v != p) dfs(v, u);
}

int lca(int u, int v) {
	if (d[u] > d[v]) swap(u, v);
	for (int i = 18; i >= 0; i--) if (d[v] - (1 << i) >= d[u]) v = L[v][i];
	if (u == v) return u;
	for (int i = 18; i >= 0; i--) if (L[u][i] && L[u][i] != L[v][i]) u = L[u][i], v = L[v][i];
	return L[u][0];
}

void solve(int u, int p, unordered_map<int, unordered_set<int>>& S) {
	for (auto& v : G[u]) {
		if (v != p) {
			unordered_map<int, unordered_set<int>> tmp;
			solve(v, u, tmp);
			if (tmp.size() > S.size()) swap(tmp, S);
			for (auto& x : tmp) {
				for (auto& i : x.s) S[x.f].insert(i);
			}
		}
	}
	for (auto& i : x[u]) S[q[i].s].insert(i);
	for (auto& i : S[T[u]]) ans[i] = 1;
	S[T[u]].clear();
	for (auto& i : y[u]) {
		if (S[q[i].s].find(i) != S[q[i].s].end()) S[q[i].s].erase(i);
	}
}

int main() {
	ifstream cin("milkvisits.in");
	ofstream cout("milkvisits.out");
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> T[i];
	for (int i = 1; i < N; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		q[i] = { ii(a, b), c };
		int l = lca(a, b);
		if (a != l) x[a].insert(i), y[l].insert(i);
		if (b != l) x[b].insert(i), y[l].insert(i);
	}
	unordered_map<int, unordered_set<int>> S;
	solve(1, 0, S);
	for (int i = 0; i < M; i++) cout << (ans[i] || T[q[i].f.f] == q[i].s || T[q[i].f.s] == q[i].s);
}
