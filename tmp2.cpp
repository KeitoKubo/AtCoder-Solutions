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
int a[max_n][max_n];
int b[max_n][max_n];
bool checked[max_n][max_n];
int h, w;

void bfs() {
	rep(i, h + 2) { b[i][0] = 0; b[i][w + 1] = 0; a[i][0] = -1; a[i][w + 1] = -1; }
	rep(i, w + 2) { b[0][i] = 0; b[h + 1][i] = 0; a[0][i] = -1; a[h + 1][i] = -1; }

	queue<pair<int, int>> Q;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { 1,0,-1,0 };
	repa(i, h) {
		repa(j, w) {
			bool flag = true;
			rep(k, 4) {
				int val = a[i][j], next = a[i + dx[k]][j + dy[k]];
				if (next < val) flag = false;
			}
			if (flag) {
				Q.push(make_pair(i, j));
				checked[i][j] = true;
			}
		}
	}

	while (!Q.empty()) {
		pii P = Q.front(); (void)Q.pop();
		rep(k, 4) {
			int x = P.first, y = P.second;
			int nx = P.first + dx[k], ny = P.second + dy[k];
			if (a[nx][ny] > a[x][y]) {
				b[nx][ny] += a[x][y];
			}
		}
	}
}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);
	cin >> h >> w;
	repa(i,h){
		repa(j, w) {
			(void)scanf("%d", &a[i][j]);
			b[i][j] = 1;
	    }
	}


	return 0;
}
