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
const int max_n = 100005;
int n;
ll c;
ll xr[max_n], xl[max_n];
ll v[max_n];
ll r_max[max_n], l_max[max_n];

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	cin >> n >> c;
	ll sum = 0;
	repa(i, n) {
		ll a;
		(void)scanf("%lld%lld", &a, &v[i]);
		xr[i] = a - sum;
		sum += xr[i];
	}
	xr[n + 1] = c - sum;

	xl[n + 1] = 0;
	for (int i = n; i >= 0; i--) {
		xl[i] = xr[i + 1];
	}

	ll r_cur = 0;
	ll r_maxi = 0;
	for (int i = 1; i <= n; i++) {
		r_cur += v[i] - xr[i];
		r_maxi = max(r_maxi, r_cur);
		r_max[i] = r_maxi;
	}
	
	ll l_cur = 0;
	ll l_maxi = 0;
	for (int i = n; i >= 1; i--) {
		l_cur += v[i] - xl[i];
		l_maxi = max(l_maxi, l_cur);
		l_max[i] = l_maxi;
	}

	ll ans = 0;
	ans = max(ans, max(l_maxi, r_maxi));

	r_cur = 0;
	r_maxi = 0;
	for (int i = 1; i <= n - 1; i++) {
		r_cur += v[i] - (ll)2 * xr[i];
		if (r_cur + l_max[i + 1] > r_maxi) {
			r_maxi = r_cur + l_max[i + 1];
		}
	}

	l_cur = 0;
	l_maxi = 0;
	for (int i = n; i >= 2; i--) {
		l_cur += v[i] - (ll)2 * xl[i];
		if (l_cur + r_max[i - 1] > l_maxi) {
			l_maxi = l_cur + r_max[i - 1];
		}
	}

	ans = max(ans, max(r_maxi, l_maxi));
	cout << ans << endl;

	return 0;
}

