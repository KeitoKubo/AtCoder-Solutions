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
	vi rank, p; //rankはその木の深さ、pは親ノード

	DisjointSet() {}
	DisjointSet(int size) {
		rank.resize(size, 0);
		p.resize(size, 0);
		rep(i, size) makeSet(i);
	}

	void makeSet(int x) {
		p[x] = x;
		rank[x] = 0;
	}

	int findSet(int x) {
		if (x != p[x]) p[x] = findSet(p[x]);
		return p[x];
	}

	bool same(int x, int y) {
		if (findSet(x) == findSet(y)) return true;
		else return false;
	}

	void link(int x, int y) {
		if (rank[x] > rank[y]) p[y] = x;
		else {
			p[x] = y;
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
const int max_n = 505;
int n, c;
int g[max_n][max_n];
int d[31][31];
int num[3][31];
int sum[3][31][31]; //jからkに色が変化するとする

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	cin >> n >> c;
	repa(i, c) {
		repa(j, c)(void)scanf("%d", &d[i][j]);
	}
	rep(i, 3) {
		rep(j, 31) num[i][j] = 0;
	}
	repa(i, n) {
		repa(j, n) {
			(void)scanf("%d", &g[i][j]);
			int k = (i + j) % 3;
			int color = g[i][j];
			num[k][color]++;
		}
	}
	rep(i, 3) {
		repa(j, c) {
			repa(k, c) {
				sum[i][j][k] = d[j][k] * num[i][j];
			}
		}
	}

	int ans = infi;
	rep(x, (int)pow(c, 3)) {
		int a[3]; //割ったあまりがiとなるマス目の色を指定
		int xx = x;
		for (int g = 2; g >= 0; g--) {
			a[g] = xx / (int)pow(c, g) + 1;
			xx %= (int)pow(c, g);
		}
		if (a[0] == a[1] || a[1] == a[2] || a[2] == a[0]) continue;

		int cur = 0;
		rep(i, 3) {
			repa(j, c) {
				cur += sum[i][j][a[i]];
			}
		}
		ans = min(ans, cur);
	}

	cout << ans << endl;

	return 0;
}
