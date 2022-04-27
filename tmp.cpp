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
const int max_n = 105;
int dp[max_n][max_n][3 * max_n];
int n, W;
int w[max_n], v[max_n];

//dp[i][j][k] := バッグにi個の荷物が入っており、j番目まで見た状態で、超過分がkである時の
//価値の最大値(1-indexで数える)
void solve() {
	rep(j, n) {
		rep(k, 3 * max_n) dp[0][j][k] = 0;
	}

	/*
	for (int i = 0; i <= n - 1; i++) { //i+1を更新することを考える
		int remain = W - w[1] * i;
		for (int j = i; j <= n - 1; j++) { //j+1番目の荷物を入れるかどうか
			int exc = w[j + 1] - w[1];
			for (int k = 0; k < 3 * max_n; k++) {
				//j+1番目の荷物が入らないとき
				if (remain - k < w[j + 1]) {
					dp[i + 1][j + 1][k] = dp[i][j][k];
				}
				//j+1番目の荷物が入るとき
				else {
					dp[i + 1][j + 1][k + exc] = max(dp[i][j][k + exc], dp[i][j][k] + v[j + 1]);
				}
			}
		}
	}
	*/

	for (int j = 0; j <= n - 1; j++) { //j+1番目の荷物を入れるかどうか
		for (int i = 0; i <= j; i++) { //i+1を更新することを考える
			int remain = W - w[1] * i;
			int exc = w[j + 1] - w[1];
			for (int k = 0; k < 3 * max_n; k++) {
				//j+1番目の荷物が入らないとき
				if (remain - k < w[j + 1]) {
					dp[i + 1][j + 1][k] = dp[i][j][k];
				}
				//j+1番目の荷物が入るとき
				else {
					dp[i + 1][j + 1][k + exc] = max(dp[i][j][k + exc], dp[i][j][k] + v[j + 1]);
				}
			}
		}
	}

	int ans = -1;
	for (int i = 0; i <= n; i++) {
		for (int k = 0; k <= 3 * (n - 1); k++) {
			ans = max(dp[i][n][k], ans);
			cout << dp[i][n][k] << " ";
		}
		cout << endl;
	}
	cout << ans << endl;

}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);

	cin >> n >> W;
	repa(i, n) {
		cin >> w[i] >> v[i];
	}

	(void)solve();

	return 0;
}
