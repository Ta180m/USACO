#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define init_io(s) ifstream cin((string)s+".in"); ofstream cout((string)s+".out"); ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define FOR(i, a, b, in) for (int i = (a); i < (b); i += in)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RFOR(i, a, b, in) for (int i = (a) - 1; i >= (b); i -= in)
#define RREP(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define trav(a, x) for (auto& a : x)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define mem(a, b) memset(a, (b), sizeof(a))
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
typedef string str;
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> ii; typedef pair<ll, ll> pl; typedef pair<ld, ld> pd;
typedef vector<int> vi; typedef vector<ll> vl; typedef vector<ld> vd;
typedef vector<ii> vii; typedef vector<pl> vpl; typedef vector<pd> vpd;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset; // WARNING: May be broken
constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
constexpr ll MOD = 1e9+7;
const ld PI = 4*atan((ld)1);

inline int imod(int i) { return i > MOD ? i - MOD : i; }

int N, pow2[100005] = { 1 };
ii S[100005];
struct seg_tree {
	int seg[800005] = { 0 }, tmp[800005] = { 0 };
	void pull(int n) { seg[n] = imod(seg[n<<1]+seg[n<<1|1]); }
	void push(int l, int r, int n) {
		seg[n] = ((ll)pow2[tmp[n]]*seg[n])%MOD;
		if (l != r) tmp[n<<1] += tmp[n], tmp[n<<1|1] += tmp[n];
		tmp[n] = 0;
	}
	void update(int x, int v, int l = 1, int r = -1, int n = 1) {
		if (r == -1) r = 2*N;
		if (tmp[n]) push(l, r, n);
		if (l == r) seg[n] = imod(v+seg[n]);
		else {
			int m = (l + r) >> 1;
			x <= m ? update(x, v, l, m, n<<1) : update(x, v, m + 1, r, n<<1|1);
			pull(n);
		}
	}
	void update_range(int a, int b, int l = 1, int r = -1, int n = 1) {
		if (r == -1) r = 2*N;
		if (tmp[n]) push(l, r, n);
		if (l > b || r < a) return;
		if (l >= a && r <= b) {
			tmp[n]++;
			push(l, r, n);
		}
		else {
			int m = (l + r) >> 1;
			update_range(a, b, l, m, n<<1), update_range(a, b, m + 1, r, n<<1|1);
			pull(n);
		}
	}
	int query(int a, int b, int l = 1, int r = -1, int n = 1) {
		if (r == -1) r = 2*N;
		if (a > b || l > b || r < a) return 0;
		if (tmp[n]) push(l, r, n);
		if (l >= a && r <= b) return seg[n];
		int m = (l + r) >> 1;
		return imod(query(a, b, l, m, n<<1) + query(a, b, m + 1, r, n<<1|1));
	}
} dp[11];

int main() {
	init_io("help");

	int fact[11] = { 1 }, nCr[11][11];
	for (int i = 0; i < 10; i++) fact[i+1] = (i+1)*fact[i];
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= i; j++) nCr[i][j] = fact[i]/fact[j]/fact[i-j];
	}
	for (int i = 0; i < 100000; i++) pow2[i+1] = imod(pow2[i]<<1);

	int K;
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> S[i].f >> S[i].s;
	sort(S, S + N);

	for (int i = 0; i < N; ++i) {
		int tmp[11];
		for (int j = 0; j <= K; ++j) {
			tmp[j] = dp[j].query(1, S[i].f);
			ll sum = dp[j].query(S[i].f, S[i].s-1);
			for (int k = 0; k <= j; ++k) {
				sum += (ll)nCr[j][k]*tmp[k];
			}
			dp[j].update(S[i].s, sum%MOD+1);
		}
		for (int j = 0; j <= K; ++j) {
			dp[j].update_range(S[i].s+1, 2*N);
		}
	}

	cout << dp[K].query(1, 2*N) << endl;
}
