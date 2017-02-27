#include <stdio.h>
#include <inttypes.h>
#define N 10000000

const long long mod = 1000000007;
long long fac[N + 1];
long long Nim0[N + 1];
long long Nim1[N + 1];

int main() {
	long long x = 1;
	for (int i = 1; i <= N; i++) {
		x *= 2;
		if (x >= mod)
			x %= mod;
	}
	fac[0] = 1;
	for (int i = 1; i <= N; i++) {
		fac[i] = (fac[i - 1] * (x - 1)) % mod;
	}
	long long n = x - 1;
	Nim0[3] = n * (n - 1) % mod;
	Nim1[3] = (fac[3] - Nim0[3] + mod) % mod;

	for (int i = 4; i <= N; i++) {
		long long t = ((Nim0[i - 2] * (i - 1) % mod) * (x - i + 1) % mod);
		Nim0[i] = (Nim1[i - 1] - t + mod) % mod;
		Nim1[i] = (fac[i] - Nim0[i] + mod) % mod;
	}

	printf("ans => %lld\n", Nim1[N]);

	return 0;
}
