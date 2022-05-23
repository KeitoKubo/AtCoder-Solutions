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
//方針: 無向グラフ、PQを使ったダイクストラ法
//計算量O(N + MlogN)
#define max_dist 1000000000000000
const int max_n = 200005;
int n, m;
vector<pair<int, ll>> v[max_n]; //町iに属する辺の情報。fitst:接続先ノード、second:辺の重み
map<pair<int, int>, int> mp; //町i,jを接続する辺の番号
int prv_node[max_n]; //最適化後における、町1～町iのパスでiの直前に通るノード
bool ischecked[max_n]; //町iの直前のノードを確定させたかどうか
ll d[max_n]; //町1～町iのパスの最小値

void dijkstra() {

	priority_queue<pair<ll, int>> PQ; //1～iへのパスの最小値*-1,i 
	repa(i, n) { d[i] = max_dist; ischecked[i] = false; }

	d[1] = 0; PQ.push(make_pair(0, 1));

	while (!PQ.empty()) {
		pair<ll, int> f = PQ.top(); (void)PQ.pop();
		int cur_node = f.second;
		ischecked[cur_node] = true;
		if (d[cur_node] < f.first * (-1)) continue;
		
		rep(i, v[cur_node].size()) {
			int next_node = v[cur_node][i].first;
			if (ischecked[next_node]) continue;
			if (d[next_node] > d[cur_node] + v[cur_node][i].second) { //更新される時に実行される部分
				d[next_node] = d[cur_node] + v[cur_node][i].second;
				prv_node[next_node] = cur_node;
				PQ.push(make_pair(d[next_node] * (-1), next_node));
			}
		}
	}
}

int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",& );
	//(void)scanf("%d%d",& ,& );
	std::cin >> n >> m;
	repa(i, m) {
		int a, b; ll c;
		(void)scanf("%d%d%lld", &a, &b, &c);
		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
		mp[make_pair(a, b)] = i;
		mp[make_pair(b, a)] = i;
	}
	(void)dijkstra();

	ll sum = 0;
	for (int i = 2; i <= n; i++) {
		int j = prv_node[i];
		if(i!=n)printf("%d ", mp[make_pair(i, j)]);
		else printf("%d\n", mp[make_pair(i, j)]);
	}

	return 0;
}

