#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
constexpr int INF = 1e9;

vector<pair<int, ii>> G[1001];

int main() {
	ifstream cin("pump.in");
	ofstream cout("pump.out");

	int N, M;
	cin >> N >> M;
	while (M--) {
		int a, b, c, f;
		cin >> a >> b >> c >> f;
		G[a].emplace_back(b, ii(c, f));
		G[b].emplace_back(a, ii(c, f));
	}

	int ans = 0;
	for (int i = 1; i <= 1000; ++i) {
		vi dist(N + 1, INF);
		dist[1] = 0;
		priority_queue<ii, vii, greater<ii>> pq;
		pq.emplace(0, 1);
		while (!pq.empty()) {
			int d = pq.top().f, u = pq.top().s;
			pq.pop();
			if (d > dist[u]) continue;
			for (auto& v : G[u]) {
				if (v.s.s >= i && d + v.s.f < dist[v.f]) {
					dist[v.f] = d + v.s.f;
					pq.emplace(dist[v.f], v.f);
				}
			}
		}
		ans = max((int)1e6 * i / dist[N], ans);
	}
	cout << ans << '\n';
}
