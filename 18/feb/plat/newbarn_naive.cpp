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

// Although this algorithm is O(n^2)
// It can solve 8 / 10 test cases
// It is also easy to code
int P[100005], A[100005], B[100005];

int main() {
	init_io("newbarn");

	int Q;
	cin >> Q;
	int u = 0;
	while (Q--) {
		char c;
		cin >> c;
		if (c == 'B') {
			cin >> P[++u];
			A[u] = B[u] = 0;
			for (int v = u, h = 1; P[v] != -1 && B[P[v]] < h; v = P[v], h++) {
				if (A[P[v]] < h) A[P[v]] = h;
				else { B[P[v]] = h; break; }
			}
		}
		else {
			int k;
			cin >> k;
			int ans = A[k];
			for (int v = k, h = 1; P[v] != -1; v = P[v], h++) {
				if (A[P[v]] == A[v] + 1) ans = max(B[P[v]] + h, ans);
				else ans = max(A[P[v]] + h, ans);
			}
			cout << ans << '\n';
		}
	}
}
