#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("restack.in");
    ofstream cout("restack.out");
    int n, c = 0, ans = 0; cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        v.push_back(c += a - b);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) ans += abs(v[i] - v[n / 2]);
    cout << ans << '\n';
}
