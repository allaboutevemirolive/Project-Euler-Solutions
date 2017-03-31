"""
SHIT CODE DON'T RUN
"""

N = 50*10**6
MOD = 10**9 + 7

def invmod(d, mod):
	u1, u3, v1, v3 = 0, mod, 1, d
	while v3:
		q = u3 / v3
		v1, v3, u1, u3 = u1 - q*v1, u3 - q*v3, v1, v3
	return u1
P = ones(N-2, dtype = bool)
P[1::2] = 0

for i in xrange(3, int(sqrt(N+1) + 1), 2):
	if P[i - 3] : P[2*i - 3::i] = 0

d, C, S, dn = 1, 36, 42, 6

for n, p in enumerate(P, start = 3):
	C = (C*6 - dn) % MOD
	if p:
		d += 1
		dn = (dn * (n - 1) * invmod(d, MOD) % MOD)
		C = (C + dn) % MOD
	else:
		dn = (dn * (n - 1) * invmod(n - 1 - d, MOD) * 5) % MOD

	S = (S + C) % MOD

print S
