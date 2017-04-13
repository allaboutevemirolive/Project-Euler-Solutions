/*
Pictured a cubic lattice from somewhere on the positive side of
the line x = y = z, looking back at the origin with the near
corner of the cube (n,n,n) pointing straight at the viewer.
This takes the form of a hexagonal grid with towers of points
corresponding to the mixtures.  Then it seemed to leap out quite
quickly that the minimal combinations that could be used were a)
the trival (n,n,n) solutions, b) two points opposite the centre
of the hexagon and c) forming the majority, combinations of 3 points
that contained the 'origin'.  All other points could then be included
(or not) with the minimal sets, giving all the many powers of two.
After that it was 'just' a matter of working out how to count them all. 

Filtering primes, mobius function, precalculating effective phi
of remaining stubs in each "tower" using mobius formulation,
counting the number of points in each plane in a double loop,
also counting total number of points and do them in powers of
two using exponentiation.
*/
#include <iostream>
typedef long long int lld;

lld mod;
lld modPower;

lld doPower(lld n, lld k) {
	k %= modPower;
	lld val = 1;
	while (k) {
		if (k % 2)
			val = (val*n) % mod;
		n = (n*n) % mod;
		k >>= 1;
	}
	return val;
}

int main() {
	lld n = 10000000;
	mod = 1;

	for (int i = 0; i < 8; ++i)
		mod *= 11;
	modPower = 10*mod / 11;

	char* prime = new char[10000001];
	char* mobius = new char[10000001];
	int* phi = new int[10000001];
	int* rems = new int[10000001];
	int* remg = new int[10000001];
	lld* spread = new lld[10000001];

	for (int i = 1; i <= 10000000; ++i) {
		prime[i] = 1;
		mobius[i] = 1;
		phi[i] = i;
		rems[i] = n % i;
		remg[i] = 0;
		spread[i] = 0;
	}

	prime[1] = 0;
	for (int i = 2; i < 3200; ++i) {
		if (prime[i]) {
			for (int goup = i + i; goup <= 10000000; goup += i)
				prime[goup] = 0;
			for (int goup = i * i; goup <= 10000000; goup += i * i)
				mobius[goup] = 0;
		}
	}

	for (int i = 2; i <= 10000000; ++i)
		if (prime[i])
			for (int goup = i; goup <= 10000000; goup += i) {
				mobius[goup] *= -1;
				phi[goup] /= i;
				phi[goup] *= (i - 1);
			}

	remg[1] = 1;
	for (lld d = 1; d <= n; ++d)
		if (mobius[d])
			for (int goup = d; goup <= n; goup += d)
				remg[goup] += (rems[goup] / d) * mobius[d];

	lld total = 0;
	lld sumphi = 0;

	for (lld i = 1; i <= n; ++i) {
		for (lld g = 1; g <= n / i; ++g)
			spread[i] += (phi[g] * (n / g - i)) + remg[g];
		spread[i] %= modPower;
		total = (total + phi[i] * spread[i]) % modPower;
		sumphi += phi[i];
	}
	sumphi %= mod;

	lld half = 3 * total;
	lld res = doPower(2, 2 * half + 1);
	res += mod - (1 + 6 * sumphi * doPower(2, half)) % mod;
	for (unsigned int i = 1; i <= n; ++i)
		res = (res + 6 * doPower(2, half - spread[i]) * phi[i]) % mod;

	std::cout << res << std::endl;
}
