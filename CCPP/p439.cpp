#include "stdafx.h"
#include <iostream>
#include <unordered_map>

using namespace std;
typedef long long ll;

const ll max = 1000000000;

inline ll sum(ll l, ll r) {
	ll n = r - 1, a = 1 + r + 1;
	(n & 1) ? a >>= 1 : n >>= 1;
	
	return (a % max) * (n % max) % max;
}

ll S(ll n) {
	static unordered_map<ll, int> cache;

	if (cache.count(n))
		return cache[n];

	ll sumi = 0, sumj = 0;
	ll q = 1, r = n, l;

	for (; r > q; ++q, r = 1) {
		l = n / (q + 1);
		sumi = (sumi + (r - l) % max * sum(0, q)) % max;
		sumj = (sumj + q * sum(l, r)) % max;
	}

	for (ll d = 1; d <= r; ++d) {
		q = n / d;
		sumi = (sumi + sum(0, q)) % max;
		sumj = (sumj + q % max * d) % max;
	}

	ll ret = sumi * sumj % max;

	for (q = 1, r = n; r > q; ++q, r = l) {
		l = n / (q + 1);
		ret = (ret - S(q) * sum(l, r)) % max;
	}

	for (ll d = 2; d <= r; ++d) {
		ret = (ret - S(n / d) * d) % max;
	}

	return cache[n] = (ret + max) % max;
}

int main() {
	cout << S(100000000000ll) << endl;
}