#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int sieve_size;
bitset<10000001> bs;
vector<int> pr;

void sieve(int size) {
	sieve_size = size;
	bs.set(); bs[0] = bs[1] = 0;
  	for (ll i = 2; i <= sieve_size; ++i) if (bs[i]) {
		for (ll j = i * i; j <= sieve_size; j += i) bs[j] = 0;
		pr.push_back(i);
	}
}

int DP[10001] = { 1 };

int main() {
	ifstream cin("exercise.in");
	ofstream cout("exercise.out");

	int N, M;
	cin >> N >> M;
	sieve(N);
	for (auto& p : pr) {
		for (int i = N; i >= 0; --i) {
			for (int j = p; j <= N - i; j *= p) DP[i + j] = ((ll)j * DP[i] + DP[i + j]) % M;
		}
	}
	int ans = 0;
	for (int i = 0; i <= N; ++i) ans = (DP[i] + ans) % M;
	cout << ans << '\n';
}
