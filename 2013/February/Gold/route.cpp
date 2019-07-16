#include <algorithm>
#include <iostream>
using namespace std;
constexpr auto INF = (int)1e9;
typedef pair<int, int> ii;

int l[40005], r[40005], dl[40005] = { 0 }, dr[40005] = { 0 };
ii E[100005];

int main() {
	int N, M, R;
	cin >> N >> M >> R;
	for (int i = 0; i < N; i++) cin >> l[i];
	for (int i = 0; i < M; i++) cin >> r[i];
	for (int i = 0; i < R; i++) cin >> E[i].first >> E[i].second;

	sort(E, E + R, [](const ii& a, const ii& b) { return a.first + a.second < b.first + b.second; });

	for (int i = 0; i < N; i++) dl[i] = l[i];
	for (int i = 0; i < M; i++) dr[i] = r[i];

	for (int i = 0; i < R; i++) {
		int u = E[i].first, v = E[i].second, a = dl[--u], b = dr[--v];
		dl[u] = max(l[u] + b, dl[u]);
		dr[v] = max(r[v] + a, dr[v]);
	}

	cout << max(*max_element(dl, dl + N), *max_element(dr, dr + N)) << endl;
}
