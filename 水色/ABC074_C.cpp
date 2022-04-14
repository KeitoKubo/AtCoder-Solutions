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
int suger_pos[1505];
int a, b, c, d, e, f;

void suger(int x) {
	if (x + c <= 1500 && suger_pos[x + c] == 0) {
		suger_pos[x + c] = 1; suger(x + c);
	}
	if (x + d <= 1500 && suger_pos[x + d] == 0) {
		suger_pos[x + d] = 1; suger(x + d);
	}
}


int main() {
	//int a = in<int>(); string b = in<string>(); char c = in<char>();
	//double d = in<double>();
	//(void)scanf("%d",&);

	cin >> a >> b >> c >> d >> e >> f;


	//水の質量としてとりうるものの配列を作成する
    //重複がないのはwater_pos2
	int x = min(a, b), y = max(a, b);
	vi water_pos, water_pos2;

	for (int i = 0; i * y * 100 <= f; i++) {
		int sum = i * y * 100;
		for (int j = 0; sum + j * x * 100 <= f; j++) {
			water_pos.push_back(sum + j * x * 100);
		}
	}
	sort(water_pos.begin(), water_pos.end());

	int cur_num = water_pos[0];
	rep(i, water_pos.size()) {
		if (water_pos[i] != cur_num) {
			water_pos2.push_back(water_pos[i]);
			cur_num = water_pos[i];
		}
	}

	//砂糖の質量としてとりうる値を発見する
	//可能なものをsuger_pos2に格納
	rep(i, 1505) suger_pos[i] = 0;
	suger(0);

	vi suger_pos2;
	suger_pos2.push_back(0);
	repa(i,1500){
		if (suger_pos[i]) suger_pos2.push_back(i);
	}

	//全探索で間に合う 30*30*1500 = 1350000
	double ans = -1.0;
	int water_ans = -1, suger_ans = -1;
	rep(i, water_pos2.size()) {
		rep(j, suger_pos2.size()) {
			int p = water_pos2[i], q = suger_pos2[j];
			if (q * 100 <= p * e && p+q<=f) {
				double cond = (double)q * 100 / (double)(p + q);
				if (cond > ans) {
					ans = cond;
					water_ans = p + q; suger_ans = q;
				}
			}
		}
	}

	cout << water_ans << " " << suger_ans << endl;

	return 0;
}
