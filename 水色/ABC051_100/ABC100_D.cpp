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
const int max_n = 1005;
ll xx[max_n], yy[max_n], zz[max_n];
ll x[max_n], y[max_n], z[max_n];
ll w[max_n];
int n, m;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	cin >> n >> m;
	rep(i, n) {
		(void)scanf("%lld%lld%lld", &xx[i], &yy[i], &zz[i]);
	}

	ll ans = -(infl - 5);
	rep(para, 8) {
		int a[3];
		int nn = para;
		for (int g = 2; g >= 0; g--) {
			if (nn >= (int)pow(2, g)) {
				a[g] = 1;
				nn -= (int)pow(2, g);
			}
			else {
				a[g] = 0;
			}
		}
		if (a[0] == 1) {
			rep(i, n) {
				x[i] = xx[i] * (-1);
			}
		}
		else {
			rep(i, n) {
				x[i] = xx[i];
			}
		}
		if (a[1] == 1) {
			rep(i, n) {
				y[i] = yy[i] * (-1);
			}
		}
		else {
			rep(i, n) {
				y[i] = yy[i];
			}
		}
		if (a[2] == 1) {
			rep(i, n) {
				z[i] = zz[i] * (-1);
			}
		}
		else {
			rep(i, n) {
				z[i] = zz[i];
			}
		}

		rep(i, n) {
			w[i] = x[i] + y[i] + z[i];
		}
		sort(w, w + n, greater<ll>());

		ll sum = 0;
		for (int i = 0; i < m; i++) {
			sum += w[i];
		}
		ans = max(ans, sum);
	}

	cout << ans << endl;

	return 0;
}
