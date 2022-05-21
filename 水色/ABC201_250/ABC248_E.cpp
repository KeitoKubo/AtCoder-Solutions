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


//---------------------------------------------------
const int max_n = 301;
ll x[max_n], y[max_n];
int n, k;

ll gcc(ll p, ll q) {
	if (p % q == 0) return q;
	else return gcc(q, p % q);
}

ll howmany[max_n];
int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);

	cin >> n >> k;
	rep(i, n) { cin >> x[i] >> y[i]; }
	repa(i, n) { howmany[i] = 0; }

	rep(i, n) {
		map<pair<ll, ll>, int> mpp;
		vector<pair<int, int>> vecc;
		rep(j, n) {
			if (i != j) {
				ll x_dif = x[i] - x[j];
				ll y_dif = y[i] - y[j];
				if (x_dif == 0) {
					mpp[make_pair(0, 1)]++;
					if (mpp[make_pair(0, 1)] == 1) {
						vecc.push_back(make_pair(0, 1));
					}
				}
				else if (y_dif == 0) {
					mpp[make_pair(1, 0)]++;
					if (mpp[make_pair(1, 0)] == 1) {
						vecc.push_back(make_pair(1, 0));
					}
				}
				else {
					ll divi = gcc(llabs(x_dif), llabs(y_dif));
					x_dif /= divi; y_dif /= divi;
					// xサイドは絶対にプラスにする
					if (x_dif < 0) {
						x_dif *= -1; y_dif *= -1;
					}
					mpp[make_pair(x_dif, y_dif)]++;
					if (mpp[make_pair(x_dif, y_dif)] == 1) {
						vecc.push_back(make_pair(x_dif, y_dif));
					}
				}
			}
		}
		rep(p, vecc.size()) {
			ll q = mpp[vecc[p]];
			howmany[q + 1]++;
		}
	}

	if (k == 1) {
		cout << "Infinity" << endl;
	}
	else {
		ll ans = 0;
		for (int i = k; i <= n; i++) {
			if (howmany[i] > 0) {
				ans += howmany[i] / (ll)i;
			}
		}
		cout << ans << endl;
	}

	return 0;
}
