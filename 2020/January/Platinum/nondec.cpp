#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
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
const ll MOD = 1e9+7;
const ll INV = 5e8+4;
const int S = 200;
const ld PI = 4*atan((ld)1);
void io(str s) {
    if (fopen((s+".in").c_str(), "r")) {
        freopen((s+".in").c_str(), "r", stdin);
        freopen((s+".out").c_str(), "w", stdout);
    } 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}


int N, K, A[50001], cl[50001][21], cr[50001][21], ans[200001];

void solve(int l, int r, vector<pair<ii, int>>& q) {
    int m = (l + r) >> 1;
    for (int i = l; i <= r; i++) memset(cl[i], 0, sizeof(cl[i])), memset(cr[i], 0, sizeof(cr[i]));
    int c[21][21] = { 0 };
    for (int i = m; i >= l; i--) {
        if (i < m) memcpy(cl[i], cl[i + 1], sizeof(cl[i]));
        for (int j = A[i]; j <= K; j++) {
            for (int k = A[i]; k <= K; k++) {
                cl[i][j] = (c[k][j] + cl[i][j]) % MOD;
                c[A[i]][j] = (c[k][j] + c[A[i]][j]) % MOD;
            }
        }
        cl[i][A[i]]++, c[A[i]][A[i]]++;
    }
    memset(c, 0, sizeof(c));
    for (int i = m + 1; i <= r; i++) {
        if (i > m + 1) memcpy(cr[i], cr[i - 1], sizeof(cr[i]));
        for (int j = A[i]; j > 0; j--) {
            for (int k = A[i]; k > 0; k--) {
                cr[i][j] = (c[j][k] + cr[i][j]) % MOD;
                c[j][A[i]] = (c[j][k] + c[j][A[i]]) % MOD;
            }
        }
        cr[i][A[i]]++, c[A[i]][A[i]]++;
    }
    vector<pair<ii, int>> ql, qr;
    for (auto& x : q) {
        if (x.f.f <= m && x.f.s > m) {
            ll cnt = 0;
            for (int i = 1; i <= K; i++) {
                cnt = (cl[x.f.f][i] + cnt) % MOD;
                ans[x.s] = (cnt * cr[x.f.s][i] + cl[x.f.f][i] + cr[x.f.s][i] + ans[x.s]) % MOD;
            }
        }
        else if (x.f.s <= m) ql.pb(x);
        else qr.pb(x);
    }
    if (l == r) return;
    solve(l, m, ql), solve(m + 1, r, qr);
}

int main() {
    io("nondec");

    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];

    int Q;
    cin >> Q;
    vector<pair<ii, int>> q(Q);
    for (int i = 0; i < Q; i++) {
        cin >> q[i].f.f >> q[i].f.s;
        q[i].f.f--, q[i].f.s--;
        q[i].s = i;
    }
    solve(0, N - 1, q);
    for (int i = 0; i < Q; i++) cout << ans[i] + (q[i].f.f == q[i].f.s) + 1 << '\n';    
}
