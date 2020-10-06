#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct point {
	ll x, y;
	point() { x = y = 0; }
	point(ll _x, ll _y) : x(_x), y(_y) {}
	bool operator < (point p) const {
		return (x == p.x && y < p.y) || x < p.x;
	}
	bool operator == (point p) const {
		return x == p.x && y == p.y;
	}
} T[305];

struct vec {
	ll x, y;
	vec(ll _x, ll _y) : x(_x), y(_y) {}
};

vec to_vec(point a, point b) {
	return vec(b.x - a.x, b.y - a.y);
}

ll dot(vec a, vec b) {
	return (a.x * b.x + a.y * b.y);
}

ll norm_sq(vec v) {
	return v.x * v.x + v.y * v.y;
}

ll cross(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r) {
	return cross(to_vec(p, q), to_vec(p, r)) > 0;
}

struct line { ll a, b, c; };

line to_line(point p1, point p2) {
	return { p2.y - p1.y, p1.x - p2.x, p1.x * p2.y - p1.y * p2.x };
}

class fenwick_tree {
private: vector<int> FT;
public:
	fenwick_tree(int N) { FT.assign(N + 1, 0); }
	void update(int x, int val) { for (; x < FT.size(); x += x & -x) FT[x] += val; }
	int query(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += FT[x]; return ret; }
	int query(int x, int y) { return query(y) - (x == 1 ? 0 : query(x - 1)); }
};

int ans[305] = { 0 };

int main() {
	ifstream cin("triangles.in");
	ofstream cout("triangles.out");
	
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) cin >> T[i].x >> T[i].y;
	sort(T, T + N);

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			line L = to_line(T[i], T[j]);

			vector<pair<ii, point>> A, B;
			for (int k = i + 1; k < N; k++) {
				if (k != i && k != j) {
					if (T[k].x * L.a + T[k].y * L.b < L.c) {
						A.emplace_back(ii(k, k), T[k]);
					}
				}
			}

			vector<ii> l, r;
			int N = A.size();
			for (int i = 0; i < N; i++) {
				l.emplace_back(A[i].first.first, i);
				r.emplace_back(A[i].first.second, i);
			}
			sort(l.begin(), l.end(), [i](const ii& a, const ii& b) { return ccw(T[b.first], T[i], T[a.first]); });
			sort(r.begin(), r.end(), [j](const ii& a, const ii& b) { return ccw(T[a.first], T[j], T[b.first]); });
			for (int i = 0; i < N; i++) {
				A[l[i].second].first.first = i + 1;
				A[r[i].second].first.second = i + 1;
			}

			sort(A.begin(), A.end());

			fenwick_tree FT(N);
			for (auto& p : A) {
				ans[FT.query(p.first.second)]++;
				FT.update(p.first.second, 1);
			}
		}
	}

	for (int i = 0; i < N - 2; i++) cout << ans[i] << endl;
}
