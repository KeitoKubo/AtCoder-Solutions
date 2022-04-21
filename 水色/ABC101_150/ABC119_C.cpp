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
int n;
int a, b, c;
int l[10];

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	cin >> n;
	cin >> a >> b >> c;
	rep(i, n) {
		cin >> l[i];
	}

	int ans = infi;
	//bit全探索
	for (int i = 0; i < (int)pow(4, n); i++) {
		vi v; int x = i;
		for (int j = n - 1; j >= 0; j--) {
			int div = (int)pow(4, j);
			v.push_back(x / div);
			x %= div;
		}

		vi aa, bb, cc;
		rep(j, v.size()) {
			if (v[j] == 1) aa.push_back(l[j]);
			else if (v[j] == 2) bb.push_back(l[j]);
			else if (v[j] == 3) cc.push_back(l[j]);
		}

		if (aa.size() == 0 || bb.size() == 0 || cc.size() == 0) continue;

		int cur = 0;
		int long_a = 0, long_b = 0, long_c = 0;
		rep(j, aa.size()) long_a += aa[j];
		rep(j, bb.size()) long_b += bb[j];
		rep(j, cc.size()) long_c += cc[j];

		cur += abs(long_a - a) + 10 * (aa.size() - 1);
		cur += abs(long_b - b) + 10 * (bb.size() - 1);
		cur += abs(long_c - c) + 10 * (cc.size() - 1);

		ans = min(ans, cur);
	}

	cout << ans << endl;

	return 0;
}
