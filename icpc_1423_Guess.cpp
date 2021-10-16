/* ICPC-1423 ::: Guess */

#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;

int sum_subrow(vector<int>* guess, int from, int to){
	return accumulate(guess->begin() + from, guess->begin() + to + 1, 0);
}

bool validate_sub_column(vector<int>* guess, vector<vector<char>>* mat, int guess_count, int col){
	for (int i = 0; i < guess_count; i++){
		if (i <= col){
			if ((*mat)[i][col] == '+' && sum_subrow(guess, i, col) <= 0){
				return false;
			} else if ((*mat)[i][col] == '-' && sum_subrow(guess, i, col) >= 0){
				return false;
			} else if ((*mat)[i][col] == '0' && sum_subrow(guess, i, col) != 0){
				return false;
			}
		}
	}
	return true;
}

bool recursive_solve(vector<int>* guess, int next, int limit, vector<vector<char>>* matrix_ptr){
	if (next == limit){
		return validate_sub_column(guess, matrix_ptr, next, next - 1);
	} else if (!validate_sub_column(guess, matrix_ptr, next, next - 1)){
		return false;
	}
	else {
		if ((*matrix_ptr)[next][next] == '0'){
			(*guess)[next] = 0;
			if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
				return true;
			}
		}
		if ((*matrix_ptr)[next][next] == '+'){
			for (int i = 1; i <= 10; i++){
				(*guess)[next] = i;
				if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
					return true;
				}
			}
		}
		if ((*matrix_ptr)[next][next] == '-'){
			for (int i = -1; i >= -10; i--){
				(*guess)[next] = i;
				if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
					return true;
				}
			}
		}
	}
	return false;
}

void solve(int n) {
	vector<int> sol(n);
	vector<vector<char>> matrix(n);
	for (int i = 0 ; i < n ; i++) {
		matrix[i].resize(n);
	}

	// input:
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i <= j){
				scanf("%c", &matrix[i][j]);
			}
		}
	}
	scanf("\n");

	// solve:
	recursive_solve(&sol, 0, n, &matrix);

	// print solution:
	for (int i = 0 ; i < n - 1 ; i++) {
		printf("%d ", sol[i]);
	}
	printf("%d\n", sol[n-1]);
}


int main() {
	int num_cases;
	int n;
	scanf("%d\n", &num_cases);
	for (int i = 0; i < num_cases; i++) {
		scanf("%d\n", &n);
		solve(n);
	}
	return 0;
}
