#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
constexpr int MAX = 1e6;

int A[5005], cnt[5005] = { 0 }, M[2000002];
ll ans[100001] = { 0 };
vector<pair<ii, int>> q;

int main() {
	ifstream cin("threesum.in");
	ofstream cout("threesum.out");

	int N, Q; cin >> N >> Q;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < Q; ++i) {
		int a, b; cin >> a >> b;
		if (a != b) q.emplace_back(ii(--a, --b), i);
	}
	sort(begin(q), end(q), [](const pair<ii, int>& a, const pair<ii, int>& b) {
		return a.f.s < b.f.s || (a.f.s == b.f.s && a.f.f > b.f.f);
	});
	
	auto it = begin(q);
	for (int i = 0; i < N; ++i) {
		ll sum = 0;
		for (int j = i - 1; j >= 0; --j) {
			int tmp = A[i] + A[j] + MAX;
			if (tmp > 0 && tmp <= 2 * MAX && M[tmp]) cnt[j] += M[tmp];
			++M[-A[j] + MAX];
			sum += cnt[j];
			while (it != end(q) && ii(j, i) == it->f) ans[(it++)->s] = sum;
		}
		for (int j = i - 1; j >= 0; --j) --M[-A[j] + MAX];
	}
	for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}
