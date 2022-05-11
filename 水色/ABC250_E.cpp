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
const int max_n = 200005;
int a[max_n], b[max_n];
int elenum_a[max_n], elenum_b[max_n]; //i番目までに含まれる要素数
vi a_nodup, b_nodup; //1番目から見ていって、重複した要素を除いた数列(最初に出てくるものだけをpushbackする)
map<int,int> mp_a, mp_b; //要素firstが初めて登場したのは何番目かをsecondに格納

int issame[max_n]; //ともに要素数がiであるとき、集合は等しいのかどうか
map<int, int> mp_iscontained_a, mp_iscontained_b;
int n, q;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	cin >> n;
	repa(i, n) { (void)scanf("%d", &a[i]); }
	repa(i, n) { (void)scanf("%d", &b[i]); }

	int elenum = 0;
	repa(i, n) {
		if (mp_a[a[i]] == 0) {
			elenum++;
			a_nodup.push_back(a[i]);
			elenum_a[i] = elenum;
			mp_a[a[i]] = i;
		}
		else {
			elenum_a[i] = elenum;
		}
	}
	elenum = 0;
	repa(i, n) {
		if (mp_b[b[i]] == 0) {
			elenum++;
			b_nodup.push_back(b[i]);
			elenum_b[i] = elenum;
			mp_b[b[i]] = i;
		}
		else {
			elenum_b[i] = elenum;
		}
	}

	//最初に等しくなる要素数はいくつか
	repa(i, n) issame[i] = false;
	int com_elenum = min(1, min(elenum_a[n], elenum_b[n]));
	
	int dif_a = 0, dif_b = 0; //片方の集合にあって、もう片方の集合に含まれない要素の数
	for (int i = com_elenum; i <= (int)min(elenum_a[n], elenum_b[n]); i++) {
		if (a_nodup[i - 1] == b_nodup[i - 1]) {
			if (dif_a == 0 && dif_b == 0) {
				issame[i] = true;
			}
		}
		else {
			int p = a_nodup[i - 1], q = b_nodup[i - 1];
			if (mp_iscontained_b[p]) {
				dif_b--;
			}
			else {
				dif_a++; mp_iscontained_a[p] = 1;
			}
			if (mp_iscontained_a[q]) {
				dif_a--;
			}
			else {
				dif_b++; mp_iscontained_b[q] = 1;
			}
			if (dif_a == 0 && dif_b == 0) {
				issame[i] = true;
			}
		}
	}

	cin >> q;
	rep(i, q) {
		int x, y;
		(void)scanf("%d%d", &x, &y);
		int fx = elenum_a[x], fy = elenum_b[y];
		if (fx == fy && issame[fx]) {
			cout << "Yes" << endl;
		}
		else cout << "No" << endl;
	}

	return 0;
}

