/* ICPC-6873 ::: Locked Treasure */
/*
 * Solution:
 * BFS
 */

#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
#include <numeric>
#include <assert.h>
#include <iostream>
#include <functional>
using namespace std;


queue<pair<vector<int>, int>> qu;
set<vector<int>> processed;

bool is_final_state(vector<int> state, int n) {
	bool all_pos = true;
	for (int i = 0; i < n; i++) {
		if (state[i] < 0) {
			all_pos = false;
		}
	}
	return all_pos;
}

int bfs(int n) {
	while (!qu.empty()) {
		pair<vector<int>, int> cur_pair = qu.front();
		qu.pop();
		vector<int> state = cur_pair.first;
		if (processed.find(state) != processed.end()){
			continue;
		}
		int depth = cur_pair.second;

//		for (int i = 0; i < n; i++) {
//			cout << state[i] << " ";
//		}
//		cout << "     depth " << depth << endl;

		if (is_final_state(state, n)) {
			return depth;
		}

		for (int i = 0; i < n; i++) {
			if (state[i] < 0) {
				vector<int> new_state = state;
				new_state[i] = abs(state[i]);
				new_state[(i - 1 + n) % n] -= abs(state[i]);
				new_state[(i + 1 + n) % n] -= abs(state[i]);

				qu.push(make_pair(new_state, depth + 1));
			}
		}
		processed.insert(state);
	}
	return -1;  // Error
}


void solve(int n) {
	vector<int> banks(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &banks[i]);
	}
	int sum_of_elems = accumulate(banks.begin(), banks.end(), 0);
	assert(sum_of_elems > 0);
	qu.push(make_pair(banks, 0));
	int ans = bfs(n);
	printf("%d\n", ans);
}


int main(){
	int n;  // number of banks
	while(scanf("%d", &n) != EOF){
		solve(n);
	}
}


