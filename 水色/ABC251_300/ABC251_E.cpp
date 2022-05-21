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
const int max_n = 300005;
ll a[max_n];
ll dp[max_n];
int n;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	std::cin >> n;
	repa(i, n) { (void)scanf("%lld", &a[i]); }

	ll ans = infl;

	//A_N を用いない場合
	repa(i, n) { dp[i] = infl; }
	dp[0] = 0;
	dp[1] = dp[2] = a[1];
	repa(i, n - 2) {
		bool flag = false;
		dp[i + 2] = min(dp[i + 2], min(dp[i], dp[i + 1]) + a[i + 1]);
		if (dp[i + 2] >= dp[i + 1] + a[i + 2]) { flag = true; dp[i + 2] = dp[i + 1] + a[i + 2]; }
		if (flag && i + 3 <= n) { dp[i + 3] = dp[i + 2]; }
	}
	ans = dp[n];

	//A_N を用いる場合
	repa(i, n) { dp[i] = infl; }
	dp[0] = 0;
	dp[1] = 0;
	rep(i, n - 2) {
		bool flag = false;
		dp[i + 2] = min(dp[i + 2], min(dp[i], dp[i + 1]) + a[i + 1]);
		if (dp[i + 2] >= dp[i + 1] + a[i + 2]) { flag = true; dp[i + 2] = dp[i + 1] + a[i + 2]; }
		if (flag && i + 3 <= n - 1) { dp[i + 3] = dp[i + 2]; i++; }
	}
	ans = min(ans, dp[n - 1] + a[n]);

	cout << ans << endl;

	return 0;
}

