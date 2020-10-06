#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;

int d[100001] = { 0 };
vector<ii> G[100001];

ii dfs(int u, int p) {
	d[u] = d[p] + 1;
	vector<ii> tmp;
	for (auto& x : G[u]) {
		if (!d[x.f] || d[x.f] > d[u]) tmp.push_back(x);
	}
	swap(G[u], tmp);
	if (G[u].size() == 1) {
		G[u][0] = dfs(G[u][0].f, u);
		return ii(G[u][0].f, G[u][0].s + 1);
	}
	else if (!G[u].empty()) {
		int tmp = 0;
		for (auto& v : G[u]) v = dfs(v.f, u);
	}
	return ii(u, 1);
}

int solve(int u, int k) {
	unordered_multiset<int> S;
	for (auto& v : G[u]) {
		int x = solve(v.f, k) + v.s;
		if (x < 0) return -1e9;
		if (x % k) S.insert(x % k);
	}
	int ret = 0;
	while (!S.empty()) {
		int x = *begin(S);
		S.erase(S.find(x));
		auto it = S.find(k - x);
		if (it == end(S)) {
			if (ret) return -1e9;
			ret = x;
		}
		else S.erase(it);
	}
	return ret;
}

int main() {
	ifstream cin("deleg.in");
	ofstream cout("deleg.out");
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
	for (int i = 1; i < N; ++i) {
		int a, b; cin >> a >> b;
		G[a].emplace_back(b, 1), G[b].emplace_back(a, 1);
	}
	int s = 1;
	for (int u = 1; u <= N; ++u) {
		if (G[u].size() > G[s].size()) s = u;
	}
	dfs(s, 0);
	for (int i = 1; i < N; ++i) cout << ((N - 1) % i == 0 ? solve(s, i) == 0 : 0);
}
