#include <bits/stdc++.h>
using namespace std;

int A[5][20005];

int main {
    int N;
    cin >> N;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < N; j++) cin >> A[i][j];
    }
    unordered_map<int, int> m[5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < N; j++) m[i][A[i][j]] = j;
    }
    sort(A[0], A[0] + N, [&m](const int& a, const int& b) {
        int c[2] = { 0 };
        for (int i = 0; i < 5; i++) c[m[i][a] < m[i][b]]++;
        return c[0] < c[1];
    });
    for (int i = 0; i < N; i++) cout << A[0][i] << '\n';    
}
