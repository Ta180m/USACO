#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define init_io ios_base::sync_with_stdio(false); cin.tie(NULL)
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
constexpr ll MOD = 1e9 + 7;
const ld PI = 4 * atan((ld)1);

int N, A[100005], B[100005];
ordered_set S[100005];

void update(int x, int y) { for (; x <= N; x += x & -x) S[x].insert(y); }
int query(int x, int y) { int ret = 0; for (; x > 0; x -= x & -x) ret += S[x].order_of_key(y + 1); return ret; }

int main() {
	ifstream cin("friendcross.in");
	ofstream cout("friendcross.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int K;
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;
		A[a] = i + 1;
	}
	for (int i = 0; i < N; ++i) {
		int b;
		cin >> b;
		B[b] = i + 1;
	}
	ll ans = 0;
	for (int i = N - K - 1; i > 0; --i) {
		update(A[i + K + 1], B[i + K + 1]);
		ans += query(N, B[i]) + query(A[i], N) - 2 * query(A[i], B[i]);
	}
	cout << ans << endl;
}
