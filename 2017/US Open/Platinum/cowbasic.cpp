#include <bits/stdc++.h>
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
constexpr auto MOD = 1000000007;

typedef vector<vi> matrix;

int d = 0;
map<str, int> var; // Variables
vector<str> program; // Program
stack<int> loop_st; // Loop stack
vector<matrix> mat_st; // Matrix stack

void mult(matrix& A, matrix& B) { // B = A * B;
	matrix res(d + 1, vi(d + 1, 0));
	for (int i = 0; i <= d; i++) {
		for (int j = 0; j <= d; j++) {
			for (int k = 0; k <= d; k++) {
				res[i][j] = ((ll)A[i][k] * (ll)B[k][j] + res[i][j]) % MOD;
			}
		}
	}
	B = res;
}

void pow(matrix& A, int n) { // A ^ n
	matrix res(d + 1, vi(d + 1, 0));
	for (int i = 0; i <= d; i++) res[i][i] = 1;
	while (n) {
		if (n % 2 == 1) mult(A, res);
		mult(A, A);
		n /= 2;
	}
	A = res;
}

int main() {
	init_io("cowbasic");

	str input;
	while (getline(cin, input)) program.push_back(input);

	for (auto& line : program) { // Record variables
		stringstream ss(line);
		str n; ss >> n;
		if (islower(n[0]) && var.find(n) == var.end()) var[n] = d++;
	}

	mat_st.push_back({});
	mat_st.back().resize(d + 1, vi(d + 1, 0));
	for (int i = 0; i <= d; i++) mat_st.back()[i][i] = 1;
	for (auto& line : program) { // Process each line
		stringstream ss(line);
		str n; ss >> n;
		if (islower(n[0])) { // Variable assignment
			matrix M(d + 1, vi(d + 1, 0));
			for (int i = 0; i <= d; i++) {
				if (i != var[n]) M[i][i] = 1;
			}
			str tmp;
			while (ss >> tmp) {
				if (islower(tmp[0])) M[var[n]][var[tmp]]++;
				else if (isdigit(tmp[0])) M[var[n]][d] += stoi(tmp);
			}
			mult(M, mat_st.back());
		}
		else if (isdigit(n[0])) { // Begin loop
			mat_st.push_back({});
			mat_st.back().resize(d + 1, vi(d + 1, 0));
			for (int i = 0; i <= d; i++) mat_st.back()[i][i] = 1;
			loop_st.push(stoi(n));
		}
		else if (n[0] == '}') { // End loop
			pow(mat_st.back(), loop_st.top());
			mult(mat_st.back(), mat_st[mat_st.size() - 2]);
			mat_st.pop_back();
			loop_st.pop();
		}
		else { // Return
			ss >> n;
			cout << mat_st.back()[var[n]][d] << endl;
		}
	}
}
