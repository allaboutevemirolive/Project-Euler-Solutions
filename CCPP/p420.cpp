#include <cstdio>
#include <map>
using namespace std;

typedef long long ll;
const int N = 10000000;
int minp[N];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int inv(int a, int m) {
	int x0 = 1, x1 = 0, x;
	int b = m, c;

	while (b) {
		int q = a / b;
		c = a - q * b;
		a = b;
		b = c;
		x = x0 - q * x1;
		x0 = x1;
		x1 = x;
	}
	return x0 < 0 ? x0 + m : x0;
}

int CRT(int m1, int r1, int m2, int r2, int d) {
	r1 %= m1;
	if (r1 < 0)
		r1 += m1;

	r2 %= m2;
	if (r2 < 0)
		r2 += m2;

	m2 /= d;
	int w = inv(m1 / d, m2);
	int x = w * (r2 - r1) / d % m2;
	if (x < 0)
		x += m2;
	return x * m1 + r1;
}

void add(map<int, int> &fct, int x, int d) {
	for (; x > 1;) {
		int p = minp[x];
		int k = 0;
		for (; x % p == 0; x /= p)
			k++;
		fct[p] += d * k;
	}
}

int calc(int n) {
	int ans = 0;
	for (int p = 2; 1 + p * p < n; p++)
		for (int q = 1; q < p && q * q + p * p < n; q++) {
			int d = gcd(p + q, p - q);
			if (2 * p * q % d) continue;
			int r = CRT(p + q, -p * q, p - q, p * q, d);
			int m = (p + q) * (p - q) / d;
			int a = (p * q - r + m) / m * m + r;
			for (; a <= (p * p + q * q) / 2; a += m) {
				map<int, int> fct;
				add(fct, p*p-a, 1);
				add(fct, a-q*q, 1);
				add(fct, m, -2);
				int cur = 1;
				for (map<int, int>::iterator it = fct.begin(); it != fct.end(); ++it)
					cur *= it->second + 1;
				ans += cur;
				if (2*a < p*p+q*q)
					ans += cur;
			}
		}
	return ans;
}

int main() {
	for (int i = 2; i < N; i++)
		if(!minp[i])
			for (int j = i; j < N; j += i)
				if(!minp[j])
					minp[j] = i;
	printf("%d\n", calc(N));

	return 0;
}
