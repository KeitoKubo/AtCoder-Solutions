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


//---------------------------------------------------
const int max_n = 102;
int n, m;
int a, b;
vi edge[max_n];
vi DAG_edge[max_n];
int shortest_path[max_n];
int color[max_n];
int indeg[max_n];
vi Tsorted_edges;

void find_shortest_path() {
	shortest_path[a] = 0;
	repa(i, n) { color[i] = 0; shortest_path[i] = infi; }

	qi Q; Q.push(a);
	color[a] = 1; shortest_path[a] = 0;
	while (!Q.empty()) {
		int now = Q.front(); (void)Q.pop();
		rep(i, edge[now].size()) {
			int next = edge[now][i];
			if (color[next] == 0 && shortest_path[now] + 1 <= shortest_path[next]) {
				Q.push(next);
				color[next] = 1;
				shortest_path[next] = shortest_path[now] + 1;
			}
		}
	}

	return;
}

void shortest_DAG() {
	repa(i, n) indeg[i] = 0;

	repa(i, n) {
		rep(j, edge[i].size()) {
			int to_go = edge[i][j];
			if (shortest_path[to_go] == shortest_path[i] + 1) {
				DAG_edge[i].push_back(to_go);
				indeg[to_go]++;
			}
		}
	}
}

void bfs(int s) {
	color[s] = 1;
	qi Q; Q.push(s);

	while(!Q.empty()){
		int now = Q.front(); (void)Q.pop();
		Tsorted_edges.push_back(now);
		color[now] = 1;
		rep(i, DAG_edge[now].size()) {
			int next = DAG_edge[now][i];
			indeg[next]--;
			if (color[next] == 0 && indeg[next] == 0) {
				Q.push(next);
			}
		}
	}
}

void Tsort() {
	repa(i, n) color[i] = 0;
	repa(i, n) {
		if (indeg[i] == 0 && color[i] == 0) bfs(i);
	}
}

ll num[max_n];
int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);

	cin >> n;
	cin >> a >> b;
	cin >> m;
	rep(i, m) {
		int x, y; cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}

	(void)find_shortest_path();
	(void)shortest_DAG();
	(void)Tsort();

	int a_pos = -1;
	rep(i, Tsorted_edges.size()) {
		if (Tsorted_edges[i] == a) {
			a_pos = i; break;
		}
	}

	repa(i, n) { num[i] = 0; }
	num[a] = 1;
	for (int x = a_pos; x < Tsorted_edges.size(); x++) {
		int cur = Tsorted_edges[x];
		rep(i, DAG_edge[cur].size()) {
			int next = DAG_edge[cur][i];
			num[next] += num[cur] % MOD;
		}
	}

	cout << num[b] << endl;

	return 0;
}
