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
#define FOR(i, a, b, in) for (int i = (a); i < (b); i += in)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RFOR(i, a, b, in) for (int i = (a) - 1; i >= (b); i -= in)
#define RREP(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define trav(a, x) for (auto& a : x)
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define mem(a, b) memset(a, (b), sizeof(a))
using namespace std;
typedef string str;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii; typedef pair<ll, ll> pl; typedef pair<ld, ld> pd;
typedef vector<int> vi; typedef vector<ll> vl; typedef vector<ld> vd;
typedef vector<ii> vii; typedef vector<pl> vpl; typedef vector<pd> vpd;
constexpr auto INF = (int)1e9;
constexpr auto LINF = (ll)1e18;

int N, A[100005];
vi ans;
pl seg[4 * 100005];

pl merge(const pl& a, const pl& b) {
	pl ret;
	if (a.first == b.first) ret = pl(a.first, (a.second + b.second < 0 ? LINF : a.second + b.second));
	else ret = (a.first > b.first ? a : b);
	return ret;
}

void update(int i, pl v, int l = 1, int r = -1, int n = 1) {
	if (r == -1) r = N;
	if (l == r) seg[n] = v;
	else {
		int m = (l + r) >> 1;
		i <= m ? update(i, v, l, m, n << 1) : update(i, v, m + 1, r, n << 1 | 1);
		seg[n] = merge(seg[n << 1], seg[n << 1 | 1]);
	}
}

pl query(int a, int b, int l = 1, int r = -1, int n = 1) {
	if (r == -1) r = N;
	if (l > b || r < a) return pl(0, 0);
	if (l >= a && r <= b) return seg[n];
	int m = (l + r) >> 1;
	return merge(query(a, b, l, m, n << 1), query(a, b, m + 1, r, n << 1 | 1));
}

int main() {
	init_io("itout");

	ll K;
	cin >> N >> K;
	for (int i = 0; i < N; i++) cin >> A[i];

	for (int i = 0; i < 4 * N; i++) seg[i] = pl(0, 0);

	for (int i = N - 1; i >= 0; i--) {
		pl q = query(A[i], N);
		if (q.first++ == 0) q.second++;
		update(A[i], q);
	}

	int d = query(1, N).first;
	cout << N - d << endl;
	for (int i = 0; i < N; i++) {
		pl q = query(A[i], A[i]);
		if (q.first == d) {
			if (K <= q.second) d--;
			else {
				ans.push_back(A[i]);
				K -= q.second;
			}
		}
		else ans.push_back(A[i]);
	}

	sort(ans.begin(), ans.end());
	for (auto& x : ans) cout << x << endl;
}
