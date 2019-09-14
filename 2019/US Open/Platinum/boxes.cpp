#include <bits/stdc++.h>
#include "grader.h"
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int d[100005], sz[100005], L[100005][20];
ii P[100005];
vi G[100005];

void addRoad(int a, int b) {
	G[a].push_back(b);
	G[b].push_back(a);
}

void dfs(int u, int p) {
	d[u] = (p != -1 ? d[p] : 0) + 1;
	sz[u] = 1;
	L[u][0] = p;
	for (int i = 0; i < 16; i++) {
		if (L[u][i] != -1) L[u][i + 1] = L[L[u][i]][i];
	}
	for (auto& v : G[u]) {
		if (v != p) {
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

int lca(int u, int v) {
	if (d[u] > d[v]) swap(u, v);
	for (int i = 16; i >= 0; i--) if (d[v] - (1 << i) >= d[u]) v = L[v][i];
	if (u == v) return u;
	for (int i = 16; i >= 0; i--) if (L[u][i] != -1 && L[u][i] != L[v][i]) u = L[u][i], v = L[v][i];
	return L[u][0];
}

int pre(int l, int u) {
	for (int i = 16; i >= 0; i--) {
		if (L[u][i] != -1 && d[L[u][i]] > d[l]) u = L[u][i];
	}
	return u;
}

void solve(int u, int p, int x, int y) {
	P[u] = ii(x, y);
	setFarmLocation(u, x, y);
	y += sz[u];
	for (auto& v : G[u]) {
		if (v != p) {
			y -= sz[v];
			solve(v, u, x, y);
			x += sz[v];
		}
	}
}

void buildFarms() {
	memset(L, -1, sizeof(L));
	dfs(0, -1);
	solve(0, -1, 1, 1);
}

void notifyFJ(int a, int b) {
	if (a == b) addBox(P[a].first, P[a].second, P[a].first, P[a].second);
	else {
		int u = lca(a, b);
		int v = pre(u, (a != u ? a : b));
		if (a != u) swap(u, v);
		addBox(P[u].first, P[u].second, P[a].first, P[a].second);
		addBox(P[v].first, P[v].second, P[b].first, P[b].second);
	}
}
