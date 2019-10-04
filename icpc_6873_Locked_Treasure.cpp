/* ICPC-6873 ::: Locked Treasure */
/*
 * Solution:
 * Each group of bandits of size m-1 must have at least one lock that they don't
 * own a key for - so that they won't be able to open the treasure room.
 * Also, they shouldn't have more than one because then some of the locks are
 * redundant. This means that every group of size m-1 will have exactly one
 * missing key (they can unlock all locks except one).
 * This lock should be unique for each group of m-1 bandits.
 * Therefore, the solution to the number of locks necessary is n choose (m-1).
 *
 * Additionally, for each lock, n-(m-1) keys must be distributed to the bandits,
 * because otherwise, there would exist some group of size m which won't have
 * a key to that lock.
 * Thus, the total number of keys is [n choose (m-1)] * [n - (m-1)].
 */

#include <cstdio>
#include <vector>
using namespace std;

#define MAX_BANDITS 31

// global lookup table for calculations of "n choose k":
vector<vector<long int>> lookup_table(MAX_BANDITS, vector<long int>(MAX_BANDITS, 0));
vector<vector<bool>> is_calculated(MAX_BANDITS, vector<bool>(MAX_BANDITS, false));

long int n_choose_k(int n, int k) {
	if (k == 0 || k == n) {
		return 1;
	}
	if (k == 1) {
		return n;
	}
	if (is_calculated[n][k]) {
		return lookup_table[n][k];
	}
	long int res = n_choose_k(n - 1, k - 1) + n_choose_k(n - 1, k);
	lookup_table[n][k] = res;
	is_calculated[n][k] = true;
	return res;
}

void solve(int n, int m) {
	long int num_locks = n_choose_k(n, m - 1);
	// The following equals to (n - (m - 1)) * num_locks / n:
	long int keys_per_bandit = n_choose_k(n - 1, m - 1);
	printf("%ld %ld\n", num_locks, keys_per_bandit);
}

int main() {
	int num_cases;
	int n, m;
	scanf("%d", &num_cases);
	for (int i = 0; i < num_cases; i++) {
		scanf("%d %d", &n, &m);
		solve(n, m);
	}
	return 0;
}
