N = 10000000
P = 1000000007

def pgcd(a, b):
	while b > 0:
		(a, b) = (b, a % b)
	return a

# Non-admissible points

NonAdm = []
u = 2
while 4 * u * u <= N:
	v = 1
	while (u * u - v * v) ** 2 > N:
		v += 1
	while v < u and (2 * u * v) ** 2 <= N:
		if ((u + v) % 2) == 1 and pgcd(u, v) == 1:
			k = 1
			while (2 * u * v * k) ** 2 <= N and (k * (u * u - v * v)) ** 2 <= N:
				NonAdm.append(((2 * u * v * k) ** 2, (k * (u * u - v * v)) ** 2))
				NonAdm.append(((k * (u *u - v * v)) ** 2, (2 * u * v * k) ** 2))
				k += 1
		v += 1
	u += 1
NonAdm.sort()
nbNonAdm = len(NonAdm)

# Factorials and their inverses modulo 1000000007

def invmod(n, p):
	(n1, p1, u1, u2) = (n, p, 1, 0)
	while p1 > 0:
		q = n1 / p1
		(n1, p1, u1, u2) = (p1, n1 - q * p1, u2, u1 - q * u2)
	return (u1 % p)

Fact = [1] * (2 * N + 1)
FactInv = [1] * (N + 1)
for k in xrange(1, 2 * N + 1):
	Fact[k] = (Fact[k - 1] * k) % P

for k in xrange(1, N + 1):
	FactInv[k] = (FactInv[k - 1] * invmod(k, P)) % P

# Binomial coefficient modulo 1000000007
def CMod(n, k):
	if k < 0 or k > n:
		return 0
	else:
		return (Fact[n] * FactInv[k] * FactInv[n - k]) % P

# F(a,b) = number of admissible paths from (a,b) to (N,N).

cache={}
def F(a, b):
	if (a, b) in cache:
		return cache[(a, b)]
	else:
		compute = CMod(2 * N - a - b, N - a)
		for U in NonAdm:
			if (U[0] > a and U[1] >= b) or (U[0] == a and U[1] > b):
				compute -= F(U[0], U[1]) * CMod(U[0] + U[1] - a - b, U[0] - a)
		compute = compute % P
		cache[(a,b)] = compute
		return compute

print(F(0, 0))
