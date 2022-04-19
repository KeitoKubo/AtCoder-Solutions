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
		if (rank[x] < rank[y]) p[x] = y;
		else {
			p[y] = x;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}

	void unite(int x, int y) {
		link(findSet(x), findSet(y));
	}
};
ll gcc(ll p, ll q) {
	if (p % q == 0) return q;
	else return gcc(q, p % q);
}

//---------------------------------------------------
const int max_n = 3005;
int n; ll p;
ll dp[max_n][max_n][6];

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	cin >> n >> p;
	repa(i, max_n - 1) {
		rep(j, max_n) {
			rep(k, 6) {
				dp[i][j][k] = 0;
			}
		}
	}

	dp[1][0][4] = 1;
	dp[1][1][5] = 1;

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= min(3 * (i - 1) - 2, n - 1); j++) {
			dp[i][j + 1][1] += 1 * dp[i - 1][j][1];
			dp[i][j + 1][1] %= p;
			dp[i][j][4] += 1 * dp[i - 1][j][1];
			dp[i][j][4] %= p;
			dp[i][j + 1][2] += 1 * dp[i - 1][j][2];
			dp[i][j + 1][2] %= p;
			dp[i][j + 2][3] += 2 * dp[i - 1][j][2];
			dp[i][j + 2][3] %= p;
			dp[i][j][4] += 1 * dp[i - 1][j][2];
			dp[i][j][4] %= p;
			dp[i][j + 1][4] += 2 * dp[i - 1][j][2];
			dp[i][j + 1][4] %= p;

			dp[i][j + 1][1] += 1 * dp[i - 1][j][3];
			dp[i][j + 1][1] %= p;
			dp[i][j][4] += 1 * dp[i - 1][j][3];
			dp[i][j][4] %= p;

			dp[i][j + 1][2] += 1 * dp[i - 1][j][4];
			dp[i][j + 1][2] %= p;
			dp[i][j + 2][3] += 2 * dp[i - 1][j][4];
			dp[i][j + 2][3] %= p;
			dp[i][j][4] += 1 * dp[i - 1][j][4];
			dp[i][j][4] %= p;
			dp[i][j + 1][4] += 2 * dp[i - 1][j][4];
			dp[i][j + 1][4] %= p;

			dp[i][j + 1][1] += 1 * dp[i - 1][j][5];
			dp[i][j + 1][1] %= p;
			dp[i][j][4] += 1 * dp[i - 1][j][5];
			dp[i][j][4] %= p;

		}
	}

	repa(i, n - 1) {
		ll ans = 0;
		ans += dp[n][i][2];
		ans %= p;
		ans += dp[n][i][4];
		ans %= p;
		ans += dp[n][i][5];
		ans %= p;
		if (i != n - 1) printf("%lld ", ans);
		else printf("%lld\n", ans);
	}

	return 0;
}
