/* ICPC-1423 ::: Guess */

#include <cstdio>
#include <vector>
using namespace std;


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
	printf("===== SOLVE =====\n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i <= j){
				printf("mat[%d][%d] = %c  ", i, j, matrix[i][j]);
			}
		}
		printf("XX \n");
	}
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


