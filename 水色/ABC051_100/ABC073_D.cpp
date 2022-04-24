#define _USE_MATH_DEFINES
#include <iostream>                         // cout, endl, cin
#include <cstdio>                           // printf, scanf
#include <string>                           // string, to_string, stoi
#include <algorithm>                        // min, max, swap, lower_bound, upper_bound
// & stable_sort, sort, reverse
#include <cmath>                            //sin(rad),cos,tan, abs, pow, sqrt, cbrt,  exp, log, log10, log2
#include <utility>                          // pair, make_pair
#include <map>                              // map
#include <set>                              // set
#include <vector>                           // vector
#include <queue>                            // queue, priority_queue
#include <stack>                            // stack
#include <list>                             // list
#include <deque>                            // deque
#include <iomanip>
#include <numeric>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
typedef pair<int, string> pis;
typedef set<int> si;
typedef map<string, int> msi;
typedef map<string, bool> msb;
typedef priority_queue<int> pqi;
typedef stack<int> sti;
typedef queue<int> qi;

#define infi 2147483647
#define infl 9223372036854775806
#define MOD  1000000007
#define EPS 0.0000000001
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define repa(i,n) for(int i=1;i<=(int)n;i++)
#define irep(i,n) for(int i=(int)n-1;i>=0;i--)

//Union Find Tree
class DisjointSet {
public:
	vi rank, p, child; //rankはその木の深さ、pは親ノード

	DisjointSet() {}
	DisjointSet(int size) {
		rank.resize(size + 1, 0);
		p.resize(size + 1, 0);
		child.resize(size + 1, 0);
		repa(i, size) makeSet(i);
	}

	void makeSet(int x) {
		p[x] = x;
		rank[x] = 0;
		child[x] = 1;
	}

	int findSet(int x) {
		if (x != p[x]) p[x] = findSet(p[x]);
		return p[x];
	}

	int howmanychilds(int x) {
		return child[x];
	}

	bool same(int x, int y) {
		if (findSet(x) == findSet(y)) return true;
		else return false;
	}

	void link(int x, int y) {
		if (rank[x] > rank[y]) {
			p[y] = x;
			child[x] += child[y];
		}
		else {
			p[x] = y; child[y] += child[x];
			if (rank[x] == rank[y]) rank[y]++;
		}
	}

	void unite(int x, int y) {
		link(findSet(x), findSet(y));
	}
};

//sort vector<pii> by second element
bool compare_by_b(pair<int, int> a, pair<int, int> b) {
	if (a.second != b.second) {
		return a.second < b.second;
	}
	else {
		return a.first < b.first;
	}
}

//---------------------------------------------------
const int max_n = 203;
int d[max_n][max_n]; //i番目の町からj番目の町までの最短の長さ
int c[max_n][max_n];
int color[max_n][max_n];
int n, m, r;
int R[10];

void dijkstra(int s) {
	repa(i, n) color[s][i] = 0;
	d[s][s] = 0;

	while (1) {
		int u = -1, minv = infi;
		repa(i, n) {
			if (d[s][i] < minv && color[s][i] != 1) {
				u = i; minv = d[s][i];
			}
		}
		if (u == -1) break;
		color[s][u] = 1;
		repa(i, n) {
			if (c[u][i] != infi && color[s][i] != 1) {
				if (d[s][i] > d[s][u] + c[u][i]) {
					d[s][i] = d[s][u] + c[u][i];
				}
			}
		}
	}
}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	cin >> n >> m >> r;
	repa(i, n) {
		repa(j, n) { if (i != j)d[i][j] = infi; c[i][j] = infi; }
	}
	rep(i, r) cin >> R[i];
	rep(i, m) {
		int x, y, z; (void)scanf("%d%d%d", &x, &y, &z);
		if (d[x][y] > z) {
			c[x][y] = z;
			c[y][x] = z;
			d[x][y] = z;
			d[y][x] = z;
		}
	}
	repa(i, n) {
		dijkstra(i);
	}

	sort(R, R + r);
	ll ans = infl;
	do {
		ll cur = 0;
		rep(i, r - 1) {
			cur += (ll)d[R[i]][R[i + 1]];
		}
		ans = min(ans, cur);
	} while (next_permutation(R, R + r));

	cout << ans << endl;

	return 0;
}
