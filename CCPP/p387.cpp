#include <iostream>
using namespace std;

#define FOR(i, k, n) for (int i = (k); i <= (n); i++)
#define LL long long

bool prime(LL x) {
	if (x < 2) return false;
	for (LL i = 2; i * i <= x; i++) 
		if (x % i == 0)
			return false;
	return true;
}

LL n = (LL) (1000000000) * 100000;
LL ans = 0;

void dfs(LL curr, int sum_of_d) {
	if (curr * 10 >= n) return;
	if (prime(curr / sum_of_d)) {
		FOR(a, 0, 9) {
			if (prime(curr * 10 + a)) {
				ans += curr * 10 + a;
			}
		}
	}

	FOR(a, 0, 9) {
		if ((curr * 10 + a) % (sum_of_d + a) == 0) {
			dfs(curr * 10 + a, sum_of_d + a);
		}
	}
}

int main() {
	FOR(a, 1, 9) dfs(a, a);
	cout << ans << endl;

	return 0;
}