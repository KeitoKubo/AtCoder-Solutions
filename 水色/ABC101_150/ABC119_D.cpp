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
vector<ll> s, t;
int a, b, q;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	//(void)scanf("%d%d",& ,&);
	cin >> a >> b >> q;
	rep(i, a) {
		ll x; (void)scanf("%lld", &x); s.push_back(x);
	}
	rep(i, b) {
		ll x; (void)scanf("%lld", &x); t.push_back(x);
	}


	rep(i, q) {
		ll ans = infl;
		ll x; (void)scanf("%lld", &x);

		//神社→寺
		ll tmp[2], v[2];
		tmp[0] = 0, tmp[1] = 0;
		v[0] = 0, v[1] = 0;
		auto ite1 = lower_bound(s.begin(), s.end(), x);
		if (ite1 != s.begin() && ite1 != s.end()) {
			tmp[0] += *ite1 - x; v[0] = *ite1;
			tmp[1] += x - *(ite1 - 1); v[1] = *(ite1 - 1);
		}
		else if (ite1 == s.begin()) {
			tmp[0] = *ite1 - x; v[0] = *ite1;
			tmp[1] = *ite1 - x; v[1] = *ite1;
		}
		else {
			tmp[0] += x - *(ite1 - 1); v[0] = *(ite1 - 1);
			tmp[1] += x - *(ite1 - 1); v[1] = *(ite1 - 1);
		}

		rep(j, 2) {
			auto ite = lower_bound(t.begin(), t.end(), v[j]);
			if (ite != t.begin() && ite != t.end()) {
				tmp[j] += min(*ite - v[j], v[j] - *(ite - 1));
			}
			else if (ite == t.begin()) {
				tmp[j] += *ite - v[j];
			}
			else {
				tmp[j] += v[j] - *(ite - 1);
			}
		}
		ans = min(ans, min(tmp[1], tmp[0]));

		//寺→神社
		tmp[0] = 0, tmp[1] = 0;
		v[0] = 0, v[1] = 0;
		ite1 = lower_bound(t.begin(), t.end(), x);
		if (ite1 != t.begin() && ite1 != t.end()) {
			tmp[0] += *ite1 - x; v[0] = *ite1;
			tmp[1] += x - *(ite1 - 1); v[1] = *(ite1 - 1);
		}
		else if (ite1 == t.begin()) {
			tmp[0] = *ite1 - x; v[0] = *ite1;
			tmp[1] = *ite1 - x; v[1] = *ite1;
		}
		else {
			tmp[0] += x - *(ite1 - 1); v[0] = *(ite1 - 1);
			tmp[1] += x - *(ite1 - 1); v[1] = *(ite1 - 1);
		}

		rep(j, 2) {
			auto ite = lower_bound(s.begin(), s.end(), v[j]);
			if (ite != s.begin() && ite != s.end()) {
				tmp[j] += min(*ite - v[j], v[j] - *(ite - 1));
			}
			else if (ite == s.begin()) {
				tmp[j] += *ite - v[j];
			}
			else {
				tmp[j] += v[j] - *(ite - 1);
			}
		}
		ans = min(ans, min(tmp[1], tmp[0]));

		cout << ans << endl;
	}


	return 0;
}
