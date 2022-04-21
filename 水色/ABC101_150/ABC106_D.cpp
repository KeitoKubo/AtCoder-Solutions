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
const int max_m = 200005;
const int max_n = 505;

int n, m, q;
int cul_sum[max_n][max_n];
int express[max_n][max_n];

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	cin >> n >> m >> q;

	rep(i, n + 1) {
		rep(j, n + 1) { cul_sum[i][j] = 0; express[i][j] = 0; }
	}
	rep(i, m) {
		int x, y;
		(void)scanf("%d%d", &x, &y);
		express[x][y]++;
	}

	//culmative sum
	/*
	for (int i = 2; i <= n; i++) cul_sum[1][i] += cul_sum[1][i - 1];
	for (int i = 2; i <= n; i++) cul_sum[i][1] += cul_sum[i - 1][1];
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= n; j++) {
			cul_sum[i][j] = cul_sum[i][j] + cul_sum[i][j - 1] + cul_sum[i - 1][j] - cul_sum[i - 1][j - 1];
		}
	}

	rep(i, q) {
		int l, r;
		(void)scanf("%d%d", &l, &r);
		int ans = cul_sum[l][r] - cul_sum[l][r - 1] - cul_sum[l - 1][r] + cul_sum[l - 1][r];
		printf("%d\n", ans);
	}
	*/

	repa(i, n) cul_sum[i][1] = express[i][1];
	repa(i, n) {
		for (int j = 2; j <= n; j++) {
			cul_sum[i][j] = express[i][j] + cul_sum[i][j - 1];
		}
	}

	rep(i, q) {
		int l, r;
		(void)scanf("%d%d", &l, &r);
		int ans = 0;
		for (int x = l; x <= r; x++) {
			ans += cul_sum[x][r] - cul_sum[x][l - 1];
		}
		printf("%d\n", ans);
	}

	return 0;
}
