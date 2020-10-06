#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;

int S[100001];
vector<ii> G[100001];

int main() {
	ifstream cin("timeline.in");
	ofstream cout("timeline.out");

	int N, M, C;
	cin >> N >> M >> C;
	for (int i = 0; i < N; ++i) cin >> S[i];
	for (int i = 0; i < C; ++i) {
		int a, b, x;
		cin >> a >> b >> x;
		G[--a].emplace_back(--b, -x);
	}
	for (int i = 0; i < N; ++i) S[i] = -S[i];
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	for (int i = 0; i < N; ++i) pq.emplace(S[i], i);
	while (!pq.empty()) {
		int d = pq.top().f, u = pq.top().s;
		pq.pop();
		if (d > S[u]) continue;
		for (auto& v : G[u]) {
			if (S[u] + v.s < S[v.f]) {
				S[v.f] = S[u] + v.s;
				pq.emplace(S[v.f], v.f);
			}
		}
	}
	for (int i = 0; i < N; ++i) cout << -S[i] << '\n';
}
