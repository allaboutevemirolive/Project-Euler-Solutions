#include <iostream>
#include <vector>

using namespace std;
typedef long long int64;

#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)

template <typename T> T gcd(T x, T y) {
	for (T t; x; t = x, x = y % x, y = t);
	return y;
}

int64 fpm(int64 b, int64 e, int64 m) {
	int64 t = 1;
	for (; e; e >>= 1, b = b * b % m) {
		e & 1 ? t = t * b % m : 0;
	}
	return t;
}

const int M = 100000000;
const int64 N = 1e11;

bool b[M + 1];

vector<int> get_primes(int n) {
	vector<int> P;

	FOR (i, 2, n) {
		if (!b[i]) P.push_back(i);
		int k = n / i;
		for (auto x : P) {
			if (x > k) break;
			b[x * i] = true;
			if (i % x == 0) break;
		}
	}
	return P;
}

auto primes = get_primes(M);

int find_root(int p) {
	int x = p - 1;
	vector<int> v;
	for (auto &y : primes) {
		if (x == 1) break;
		if (y * y > x) break;
		if (x % y == 0) {
			v.push_back((p - 1) / y);
			for (; x /= y, x % y == 0; );
		}
	}
	if (x != 1) v.push_back((p - 1) / x);
	x = p - 1;
	FOR (i, 2, p) {
		bool b = true;
		for (auto y : v)
			if (fpm(i, y, p) == 1) {
				b = false;
				break;
			}
		if (b) return i;
	}
	return -1;
}

int inv[15];

int main() {
	int64 ans = 0;
	int cnt = 0;

	FOR (i, 1, 15) {
		int g = gcd(i, 15);
		int x = i / g;
		int y = 15 / g;
		int e = 1;
		for (; y * e % x != 1 % x; ++e);
		inv[i % 15] = e;
	}

	for (auto p : primes) {
		int x = find_root(p);
		if (++cnt % 100000 == 0) {
			cerr << p << " " << x << endl;
		}
		int g = gcd(p - 1, 15);
		int y = (p - 1) / g;
		int64 b = fpm(x, (p - 1) / (2 * g) * inv[(p - 1) % 15] % y, p);
		int64 m = fpm(x, y, p);

		FOR (t, 1, g) {
			ans += (N + p - b) / p * p;
			b = b * m % p;
		}
	}

	cout << ans << endl;

	return 0;
}
