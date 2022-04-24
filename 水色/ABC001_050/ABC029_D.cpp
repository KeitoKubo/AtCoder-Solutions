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
int a[11]; //0～10^i-1までで、1の登場する回数
int num[11]; //nのi桁目の数
int x[11]; //nのi桁目まで取り出した数

int func(int p) {//xはその位の数、pは桁数
	int ans = 0;
	if (p == 1) {
		if (num[p] == 0)ans = 0;
		else ans = 1;
	}
	else {
		for (int i = 0; i <= num[p] - 1; i++) {
			if (i == 1) ans += (int)pow(10, p - 1) + a[p - 1];
			else ans += a[p - 1];
		}
		if (num[p] == 1) { ans += x[p - 1] + 1 + func(p - 1); }
		else { ans += func(p - 1); }
	}
	return ans;
}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	int n; cin >> n;
	a[1] = 1;
	for (int i = 2; i <= 9; i++) a[i] = (int)pow(10, i - 1) + 10 * a[i - 1];
	int m = n;
	for (int y = 8; y >= 0; y--) {
		num[y + 1] = m / (int)pow(10, y);
		x[y] = m % (int)pow(10, y);
		m = x[y];
	}

	int q = -1;
	for (int z = 9; z >= 1; z--) {
		if (num[z] >= 1) {
			q = z; break;
		}
	}

	cout << func(q) << endl;


	return 0;
}
