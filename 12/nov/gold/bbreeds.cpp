#include <iostream>
#include <string>
using namespace std;

int main() {
	string S; cin >> S;
	int x = 0, DP[1005] = { 1 };
	for (auto c : S) {
		if (c == '(') for (x++, int i = x; i > 0; i--) DP[i] = (DP[i - 1] + DP[i]) % 2012;
		else for (x--, int i = 0; i <= x; i++) DP[i] = (DP[i] + DP[i + 1]) % 2012;
		DP[x + 1] = 0;
	}
	cout << DP[0] << endl;
}
