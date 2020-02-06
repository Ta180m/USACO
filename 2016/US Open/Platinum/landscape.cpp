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

vi A, B;
priority_queue<ll> p1, p2;

int main() {
	init_io("landscape");

	ll N, X, Y, Z, ans = 0;
	cin >> N >> X >> Y >> Z;
	for (int i = 0; i < N; i++) {
		int A, B;
		cin >> A >> B;
		for (int j = A; j < B; j++) {
			ll cost = X;
			if (!p2.empty() && i * Z - p2.top() < X) {
				cost = i * Z - p2.top();
				p2.pop();
			}
			ans += cost;
			p1.push(i * Z + cost);
		}
		for (int j = B; j < A; j++) {
			ll cost = Y;
			if (!p1.empty() && i * Z - p1.top() < Y) {
				cost = i * Z - p1.top();
				p1.pop();
			}
			ans += cost;
			p2.push(i * Z + cost);
		}
	}
	cout << ans << endl;
}
