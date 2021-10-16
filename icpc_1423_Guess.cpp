/* ICPC-1423 ::: Guess */

#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;


int sum_subrow(vector<int>* guess, int from, int to){
	return accumulate(guess->begin() + from, guess->begin() + to + 1, 0);
}


bool solve_aux(vector<int>* guess, vector<vector<char>>* mat){
	for (int i = 0; i < (int)mat->size(); i++){
		for (int j = 0; j < (int)mat->size(); j++){
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
	if (next == limit){
		return solve_aux(guess, matrix_ptr);
	} else {
		for (int i = -10; i <= 10; i++){
			(*guess)[next] = i;
//			printf("a[%d] = %d\n", next, i);
			if (recursive_solve(guess, next + 1, limit, matrix_ptr)){
				return true;
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



	for (int i = 0 ; i < n ; i++) {
		printf("%d ", sol[i]);
	}
	printf("\n");
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


