#include <iostream>
#include <vector>

using namespace std;

#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)

const int N = 10000000;

bool b[N + 1];
int ufs[N + 1];

vector<int> get_primes(int n) {
	vector<int> P;

	FOR (i, 2, n) {
		if (!b[i]) {
			P.push_back(i);
		}

		int k = n / i;
		for (auto x : P) {
			if (x > k) break;
			b[x * i] = true;
			if (i % x == 0) break;
		}
	}
	return P;
}

int find(int t) {
	return ufs[t] ? ufs[t] = find(ufs[t]) : t;
}

void unite(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) ufs[x] = y;
}

int main() {
	auto P = get_primes(N);

	auto ans = 011;
	for (auto x : P) {
		for (auto k = 1; x >= k; k *= 10) {
			auto t = x / k % 10;
			auto y = x - k * t;
			FOR (i, 0, t - 1) {
				if (!b[y] && y != 1 && y * 10 >= k) {
					int w = find(y);
					if (w != x) ufs[w] = x;
				}
				y += k;
			}
		}
		if (find(2) != x) {
			ans += x;
			cout << "x:" << x << endl;
		}
	}

	cout << ans << endl;
	return 0;
}
