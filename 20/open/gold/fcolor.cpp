#include <bits/stdc++.h>
using namespace std;

int cnt = 0, c[200002], p[200002], ans[200002];
bitset<200002> vis;
vector<int> G[200002], H[200002];

void dfs(int u) {
	vis[u] = 1;
	for (auto& v : G[u]) {
		if (!vis[v]) dfs(v);
		if (c[v]) c[u] = max(p[c[v]], c[u]);
	}
	for (auto& v : H[u]) {
		if (!vis[v]) dfs(v);
		if (c[u]) c[v] = max(p[c[u]], c[v]);
	}
	if (!c[u]) c[u] = ++cnt;
	for (auto& v : G[u]) if (c[v]) p[c[v]] = max(c[u], p[c[v]]);
	for (auto& v : H[u]) if (c[v]) p[c[u]] = max(c[v], p[c[u]]);
}

int main() {
	ifstream cin("fcolor.in");
	ofstream cout("fcolor.out");

	int N, M; cin >> N >> M;
	while (M--) {
		int a, b; cin >> a >> b;
		G[b].push_back(a), H[a].push_back(b);
	}
	for (int u = 1; u <= N; ++u) dfs(u);
	vis.reset();
	for (int u = 1; u <= N; ++u) dfs(u);
	cnt = 0;
	for (int u = 1; u <= N; ++u) if (!ans[c[u]]) ans[c[u]] = ++cnt;
	for (int u = 1; u <= N; ++u) cout << ans[c[u]] << '\n';
}
