#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 1e5+5;

int ans, D[2*MX];
vector<int> G[MX], H[2*MX];

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);

	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M;
		for (int u = 1; u <= N; ++u) G[u].clear();
		for (int u = 1; u <= 2*N; ++u) H[u].clear();
		for (int i = 0; i < M; ++i) {
			int x, y; cin >> x >> y;
			G[x].push_back(y), G[y].push_back(x);
			H[x].push_back(y+N), H[y+N].push_back(x);
			H[y].push_back(x+N), H[x+N].push_back(y);
		}
		
		for (int u = 1; u <= 2*N; ++u) D[u] = 1e9;
		queue<int> q;
		D[1] = 0, q.push(1);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int v : H[u]) if (D[v] == 1e9)
				D[v] = D[u]+1, q.push(v);
		}

		if (*max_element(D+1, D+2*N+1) == 1e9) {
			cout << N-1 << '\n';
			continue;
		}

		/*vector<ii> C;
		C.emplace_back(0, 0);
		for (int u = 1; u <= N; ++u) {
			C.emplace_back(D[u], D[u+N]);
		}*/

		ans = 0;
		map<ii, int> f;
		map<ii, vector<int>> b;
		for (int u = 1; u <= N; ++u) {
			ii p(min(D[u], D[u+N]), max(D[u], D[u+N]));
			++f[p], b[p].push_back(u);
		}
		map<ii, int> ea;
		for (auto [p, c] : f) {
			int pr = ea[ii(p.f-1, p.s+1)];
			if (p.f+1 == p.s) {
				if (p.f == 0) ans += (c+1)/2;
				else if (f[ii(p.f-1, p.s-1)]) ans += max((c-pr)+(pr+1)/2, (c+1)/2);
				else {
					if (pr < c) ans += c-pr;
					ans += (c+1)/2;
				}
			}
			else {
				ans += c;
				if (p.f == 0) ea[p] = c;
				else if (f[ii(p.f-1, p.s-1)]) ea[p] += min(c, pr);
				else {
					if (pr < c) ans += c-pr;
					ea[p] = c;
				}
			}
		}
		cout << ans << '\n';
	}
}
