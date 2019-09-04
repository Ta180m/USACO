#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

struct point { long long x, y; };

long long F[100005];

bool cw(point a, point b, point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0; }

int main() {
	ifstream fin("balance.in");
	ofstream fout("balance.out");

	int N;
	fin >> N;
	for (int i = 0; i < N; i++) fin >> F[i + 1];
	F[0] = F[N + 1] = 0;

	vector<point> P;
	for (int i = 0; i < N + 2; i++) P.push_back({ i, F[i] });

	sort(P.begin(), P.end(), [](const point &a, const point &b) { return a.x * b.y < b.x * a.y || (a.x * b.y == b.x * a.y && a.x < b.x); });

	vector<point> S;
	S.push_back(P[0]);
	S.push_back(P[1]);

	for (int i = 2; i < N + 2; i++) {
		while (S.size() > 1 && !cw(S[S.size() - 2], S[S.size() - 1], P[i])) S.pop_back();
		S.push_back(P[i]);
	}

	for (int i = 0; i < S.size() - 1; i++) {
		for (int j = 0; j < S[i + 1].x - S[i].x; j++) {
			if (!i && !j) continue;
			if (S[i].y < S[i + 1].y) cout << 100000 * S[i].y + (100000 * j * (S[i + 1].y - S[i].y)) / (S[i + 1].x - S[i].x) << endl;
			else cout << 100000 * S[i + 1].y + (100000 * (S[i + 1].x - S[i].x - j) * (S[i].y - S[i + 1].y)) / (S[i + 1].x - S[i].x) << endl;
		}
	}
}