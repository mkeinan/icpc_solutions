/* ICPC-1423 ::: Guess */

#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;


int sum_subrow(vector<int>* guess, int from, int to){
	return accumulate(guess->begin() + from, guess->begin() + to + 1, 0);
}


bool validate_sub_matrix(vector<int>* guess, vector<vector<char>>* mat, int guess_count){
	for (int i = 0; i < guess_count; i++){
		for (int j = 0; j < guess_count; j++){
			if (i <= j){
//				printf("from %d to %d = %d \n", i, j, sum_subrow(guess, i, j));
				if ((*mat)[i][j] == '+' && sum_subrow(guess, i, j) <= 0){
					return false;
				} else if ((*mat)[i][j] == '-' && sum_subrow(guess, i, j) >= 0){
					return false;
				} else if ((*mat)[i][j] == '0' && sum_subrow(guess, i, j) != 0){
					return false;
				}
			}
		}
	}
	return true;
}


bool recursive_solve(vector<int>* guess, int next, int limit, vector<vector<char>>* matrix_ptr){
//	printf("-DD- recursive_solve: next = %d  \n", next);
	if (next == limit){
		return validate_sub_matrix(guess, matrix_ptr, limit);
	} else if (!validate_sub_matrix(guess, matrix_ptr, next)){
//		printf("-D- !validate_sub_matrix\n");
		return false;
	}
	else {
//		printf("-DDD- recursive_solve: else. (*matrix_ptr)[next][next] = %d %d\n", (*matrix_ptr)[next][next], '-');
		if ((*matrix_ptr)[next][next] == '0'){
			(*guess)[next] = 0;
//			printf("-D1- a[%d] = %d\n", next, 0);
			if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
				return true;
			}
		}
		if ((*matrix_ptr)[next][next] == '+'){
			for (int i = 1; i <= 10; i++){
				(*guess)[next] = i;
//				printf("-D2- a[%d] = %d\n", next, i);
				if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
					return true;
				}
			}
		}
		if ((*matrix_ptr)[next][next] == '-'){
			for (int i = -1; i >= -10; i--){
				(*guess)[next] = i;
//				printf("-D3- a[%d] = %d\n", next, i);
				if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
					return true;
				}
			}
		}
	}
//	printf("-D- recursive_solve: END => false\n");
	return false;
}


void solve(int n) {
	vector<int> sol(n);
	vector<vector<char>> matrix(n);
	for (int i = 0 ; i < n ; i++) {
		matrix[i].resize(n);
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i <= j){
				scanf("%c", &matrix[i][j]);
			}
		}
	}
	scanf("\n");

	// DEBUG
//	printf("===== SOLVE =====\n");
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < n; j++){
//			if (i <= j){
//				printf("mat[%d][%d] = %c  ", i, j, matrix[i][j]);
//			}
//		}
//		printf("XX \n");
//	}


	recursive_solve(&sol, 0, n, &matrix);



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


