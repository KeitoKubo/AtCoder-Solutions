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
const int max_n = 200004;
int a[max_n];
int bit[max_n][24];
int seg[max_n];
int n;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	cin >> n;
	repa(i, n) {
		(void)scanf("%d", &a[i]);
	}
	
	repa(i, n) {
		int x = a[i];
		for (int k = 19; k >= 0; k--) {
			if (x >= (int)pow(2, k)) {
				bit[i][k] = 1; x -= (int)pow(2, k);
			}
			else {
				bit[i][k] = 0;
			}
		}
	}

	//0の管理
	int s = -1;
	repa(i, n) {
		if (a[i] == 0) {
			s = i; break;
		}
	}
	map<int, int> mp;
	if (s != -1) {
		int cur = s;
		for (int i = s+1; i <= n; i++) {
			if (a[i] == 0) {
				if (a[i - 1] != 0) {
					cur = i;
				}
			}
			else {
				if (a[i - 1] == 0) {
					for (int j = cur; j <= i - 1; j++) {
						mp[j] = i - 1;
					}
				}
			}
		}
		if (a[n] == 0) {
			for (int j = cur; j <= n; j++) {
				mp[j] = n;
			}
		}
	}


	int cur[24];
	repa(i, n) {
		seg[i] = 1;
		rep(k, 20) {
			if (bit[i][k] == 1) cur[k] = 1;
			else cur[k] = 0;
		}
		bool flag = false;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] == 0) {
				seg[i] += mp[j] - j + 1;
				j = mp[j];
			}
			else {
				rep(k, 20) {
					if (bit[j][k] == 1 && cur[k] == 1) {
						flag = true; break;
					}
					else if (bit[j][k] == 1) {
						cur[k] = 1;
					}
				}
				if (flag) break;
				seg[i]++;
			}
		}
	}

	ll sum = 0;
	repa(i, n) {
		sum += (ll)seg[i];
	}
	cout << sum << endl;

	return 0;
}

