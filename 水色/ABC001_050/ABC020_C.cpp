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
const int max_range = 12;
char s[max_range][max_range];
ll d[max_range][max_range];
bool flg[max_range][max_range];
int h, w;
int sx, sy, gx, gy;
ll T;

bool ispos(ll x) {
	repa(i, h) {
		repa(j, w) {
			d[i][j] = infl; flg[i][j] = 0;
	    } 
	}
	d[sx][sy] = 0;

	ll minv = infl;
	int ux = -1, uy = -1;
	
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { 1,0,-1,0 };
	while (1) {
		minv = infl; ux = -1; uy = -1;
		repa(i, h) {
			repa(j, w) {
				if (d[i][j] < minv && !flg[i][j]) {
					minv = d[i][j]; ux = i; uy = j;
				}
			}
		}

		if (ux == -1) break;
		flg[ux][uy] = 1;
		int nnx = -1, nny = -1;
		char nc = '-';
		ll nv = infl;
		rep(i, 4) {
			int nx = ux + dy[i], ny = uy + dx[i];
			if (nx >= 1 && nx <= h && ny >= 1 && ny <= w) {
				if (!flg[nx][ny]) {
					ll v;
					if (s[nx][ny] == '#') v = x;
					else v = 1;
					d[nx][ny] = min(d[nx][ny], d[ux][uy] + v);
					if (v < nv) {
						nnx = nx; nny = ny; nc = s[nx][ny]; nv = v;
					}
				}
			}
		}
	}

	if (d[gx][gy] <= T) return true;
	else return false;
}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	cin >> h >> w >> T;
	repa(i, h) {
		repa(j, w) {
			cin >> s[i][j];
			if (s[i][j] == 'S') { sx = i; sy = j; }
			if (s[i][j] == 'G') { gx = i; gy = j; }
		}
	}

	ll l = 1, r = T;
	while (r - l > 1) {
		ll mid = (l + r) / 2;
		bool flag = ispos(mid);
		if (flag) { l = mid; }
		else r = mid;
	}

	cout << l << endl;

	return 0;
}

