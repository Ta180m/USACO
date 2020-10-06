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

char G[2002][2002];
ll pow2[2002] = { 1 }, DP[2002][2002][2] = { 0 };

int main() {
	init_io("sprinklers2");

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) cin >> G[i][j];
	}

	for (int i = 0; i < N; ++i) pow2[i + 1] = (pow2[i] << 1) % MOD;
	
	DP[0][0][1] = 1;
	for (int i = 0; i < N; ++i) {
		ll l = 0, r = 0, sum = 0;
		for (int j = 1; j < N; ++j) r += G[i][j] == '.';
		for (int j = 0; j <= N; ++j) {
            if (j && j < N) r -= G[i][j] == '.';
            DP[i + 1][j][j == N] = (pow2[l] * pow2[r] % MOD) * (((j && G[i][j - 1] == '.') + 1) * (DP[i][j][0] + DP[i][j][1]) + (j && G[i][j - 1] == '.') * sum) % MOD;
            if (j < N && G[i][j] == '.') DP[i + 1][j][1] = DP[i + 1][j][0];
            if (j < N) sum = (DP[i][j][1] + sum) % MOD;
            if (j) l += G[i][j - 1] == '.';
		}
	}
	ll ans = 0;
	for (int i = 0; i <= N; ++i) ans = (DP[N][i][1] + ans) % MOD;
	cout << ans << '\n';
}
