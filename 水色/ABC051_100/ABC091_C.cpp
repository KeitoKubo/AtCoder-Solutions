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
vector<pair<int, int>> vec_r, vec_b, vec_rx, vec_ry, vec_bx;
map<pair<int, int>, int> mp1, mp2;

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	int n; cin >> n;
	rep(i, n) {
		int x, y; cin >> x >> y;
		vec_r.push_back(make_pair(x, y));
		mp1[make_pair(x, y)] = i;
	}
	rep(i, n) {
		int x, y; cin >> x >> y;
		vec_b.push_back(make_pair(x, y));
		mp2[make_pair(x, y)] = i;
	}

	//sort them
	sort(vec_b.begin(), vec_b.end());

	rep(i, n) {
		vec_rx.push_back(vec_r[i]);
	}
	sort(vec_rx.begin(), vec_rx.end());
	rep(i, n) {
		int x = vec_r[i].first, y = vec_r[i].second;
		pii P = make_pair(y, x);
		vec_ry.push_back(P);
	}
	sort(vec_ry.begin(), vec_ry.end());

	//solution
	bool isused[105];
	rep(i, n) isused[i] = false;
	int ans_1 = 0, ans_2 = 0;
	rep(i, n) {
		int x = vec_b[i].first, y = vec_b[i].second;
		for (int j = vec_rx.size() - 1; j >= 0; j--) {
			if (vec_rx[j].first < x && vec_rx[j].second < y) {
				if (!isused[j]) {
					ans_1++; isused[j] = true; break;
				}
			}
		}
	}

	rep(i, n) { isused[i] = false; }
	rep(i, n) {
		int x = vec_b[i].first, y = vec_b[i].second;
		for (int j = vec_rx.size() - 1; j >= 0; j--) {
			if (vec_ry[j].first < y && vec_ry[j].second < x) {
				if (!isused[j]) {
					ans_2++; isused[j] = true; break;
				}
			}
		}
	}

	cout << max(ans_1,ans_2) << endl;

	return 0;
}
