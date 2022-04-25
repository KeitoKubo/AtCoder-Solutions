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
const int max_w = 10005;
const int max_n = 52;
int dp[max_n][max_n][max_w];
int sheet[max_n][max_w];
int w[max_n], v[max_n];
int W, n, K;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	cin >> W >> n >> K;
	rep(i, n) {
		(void)scanf("%d%d", &w[i], &v[i]);
	}

	rep(i, n + 1) {
		rep(j, K + 1) {
			rep(k, W + 1) { dp[i][j][k] = 0; }
		}
	}

	//dp[i][j][k] := i番目の荷物まででj個の荷物を入れる時、重さがkを超えないように選んだ時の価値の最大値
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= min(i, K - 1); j++) {
			for (int k = 0; k <= W; k++) {
				if (k < w[i]) {
					dp[i + 1][j][k] = dp[i][j][k];
				}
				else {
					if (j != 0)dp[i + 1][j][k] = max(dp[i][j][k], dp[i][j - 1][k - w[i]] + v[i]);
					else dp[i + 1][j][k] = dp[i][j][k];
					dp[i + 1][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k - w[i]] + v[i]);
				}
			}
		}
	}

	int ans = -1;
	rep(i, K + 1) {
		ans = max(ans, dp[n][i][W]);
	}
	cout << ans << endl;

	return 0;
}
