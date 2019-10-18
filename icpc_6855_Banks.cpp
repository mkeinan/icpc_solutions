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





int bfs4(int n) {
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

//		int lowest_abs_sum = 2147483647;
		long int lowest_abs_sum = (long int)92233720368;
		vector<int> chosen_state;
		for (int i = 0; i < n; i++) {
			if (state[i] < 0) {
				vector<int> new_state = state;
				new_state[i] = abs(state[i]);
				new_state[(i - 1 + n) % n] -= abs(state[i]);
				new_state[(i + 1 + n) % n] -= abs(state[i]);

//				qu.push(make_pair(new_state, depth + 1));

				long int abs_sum = 0;
				for (int k = 0; k < n; k++) {
					abs_sum += (long int)abs(new_state[k]);
				}
//				cout << "lowest_abs_sum" << lowest_abs_sum << endl;
//				cout << "abs_sum = " << abs_sum << endl;
				if (abs_sum < lowest_abs_sum){
//					cout << "OK" << endl;
					lowest_abs_sum = abs_sum;
					chosen_state = new_state;
				}
			}
		}
		qu.push(make_pair(chosen_state, depth + 1));
//		processed.insert(state);
	}
	return -1;  // Error
}


/*
int limit = 2147483647;

int bfs3(int n) {
	while (!qu.empty()) {
		pair<vector<int>, int> cur_pair = qu.front();
		qu.pop();
		vector<int> state = cur_pair.first;
		if (processed.find(state) != processed.end()){
			continue;
		}
		int depth = cur_pair.second;

		for (int i = 0; i < n; i++) {
			cout << state[i] << " ";
		}
		cout << "     depth " << depth << endl;

		if (is_final_state(state, n)) {
			return depth;
		}

		int abs_sum = 0;
		for (int i = 0; i < n; i++) {
			abs_sum += abs(state[i]);
		}
		if (abs_sum > limit){
			cout << "     BACKTRACK CUT! " << depth << endl;
			continue;
		} else {
			limit = abs_sum;
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


int dir = 0;

int bfs2(int n) {
	while (!qu.empty()) {
		pair<vector<int>, int> cur_pair = qu.front();
		qu.pop();
		vector<int> state = cur_pair.first;
		if (processed.find(state) != processed.end()){
			continue;
		}
		int depth = cur_pair.second;

		for (int i = 0; i < n; i++) {
			cout << state[i] << " ";
		}
		cout << "     depth " << depth << endl;

		if (is_final_state(state, n)) {
			return depth;
		}

		// just find the smallest and turn it...

		int min = state[0];
		int idx_min = 0;
		if (dir == 0) {
			for (int i = 0; i < n; i++) {
				if (state[i] < min) {
					min = state[i];
					idx_min = i;
				}
			}
		} else {
			for (int i = n-1; i >= 0; i--) {
				if (state[i] < min) {
					min = state[i];
					idx_min = i;
				}
			}
		}
		vector<int> new_state = state;
		new_state[idx_min] = abs(state[idx_min]);
		new_state[(idx_min - 1 + n) % n] -= abs(state[idx_min]);
		new_state[(idx_min + 1 + n) % n] -= abs(state[idx_min]);

		qu.push(make_pair(new_state, depth + 1));
		processed.insert(state);
	}
	return -1;  // Error
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

		for (int i = 0; i < n; i++) {
			cout << state[i] << " ";
		}
		cout << "     depth " << depth << endl;

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
*/

void solve(int n) {
	vector<int> banks(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &banks[i]);
	}
//	int sum_of_elems = accumulate(banks.begin(), banks.end(), 0);
//	assert(sum_of_elems > 0);
	qu.push(make_pair(banks, 0));
//	int ans = bfs(n);
	int ans = bfs4(n);
	printf("%d\n", ans);
}


int main(){
	int n;  // number of banks
	while(scanf("%d", &n) != EOF){
		solve(n);
	}
}


