#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int N, ans = 0, pre[50005], d[50005] = { 0 }, L[20][50005] = { 0 };
vector<int> G[50005];

void dfs(int u, int p) {
	d[u] = d[p] + 1;
	L[0][u] = p;
	for (int i = 0; (1 << i) < N; i++) if (L[i][u]) L[i + 1][u] = L[i][L[i][u]];
	for (int v : G[u]) if (v != p) dfs(v, u);
}

int lca(int u, int v) {
	if (d[u] > d[v]) swap(u, v);
	for (int i = log2(N); i >= 0; i--) if (d[v] - (1 << i) >= d[u]) v = L[i][v];
	if (u == v) return u;
	for (int i = log2(N); i >= 0; i--) if (L[i][u] && L[i][u] != L[i][v]) u = L[i][u], v = L[i][v];
	return L[0][u];
}

void solve(int u, int p) {
	for (int v : G[u]) {
		if (v != p) {
			solve(v, u);
			pre[u] += pre[v];
		}
	}
	ans = max(pre[u], ans);
}

int main() {
	ifstream cin("maxflow.in");
	ofstream cout("maxflow.out");

	int K;
	cin >> N >> K;
	for (int i = 0; i < N - 1; i++) {
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}

	dfs(1, 0);

	while (K--) {
		int s, t;
		cin >> s >> t;
		pre[s]++, pre[t]++;
		pre[L[0][lca(s, t)]]--, pre[lca(s, t)]--;
	}

	solve(1, 0);
	cout << ans << endl;
}
