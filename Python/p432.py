import numpy
import sys
from math import sqrt

def primes_to_n(n):
    sieve = numpy.ones(n/3 + (n%6 == 2), dtype=numpy.bool)
    for i in xrange(1, int(n**0.5) / 3+1):
        if sieve[i]:
            k = 3*i+1 | 1
            sieve[k*k/3::2*k] = False
            sieve[k*(k-2*(i&1) + 4) / 3::2*k] = False
    return numpy.r_[2, 3, ((3*numpy.nonzero(sieve)[0][1:]+1)|1)]

N = 10**7
P = [2, 3, 5, 7, 11, 13, 17]
Q = primes_to_n(N)

# Tabular values for Mobius function
Mu = [1] + (N + 1)
Mu[0] = 0
for p in Q:
    for k in range(p, N + 1, p):
        Mu[k] = -Mu[k]
    for k in range(p * p, N + 1, p * p):
        Mu[k] = 0

# Tabular values for Mertens function
M = [0] * (N + 1)
c = 0
for i, x in enumerate(Mu):
    c += x
    M[i] = c

# Recursive calculation of Mertens function for larger values
md = {} # cache
def Merten(n):
    if n < N: return M[n]
    if not md.has_key(n):
        b = int(sqrt(n))
        md[n] = 1 - sum(Merten(n / k) for k in range(2, b + 1)) - sum(M[r] * (n / r - n / (r + 1))
                for r in range(1, n / (b + 1) + 1))
    return md[n]

# Sum of Euler Phi is calculated with Mertens function
def sum_euler_phi(n):
    b = int(sqrt(n))
    return (sum(Mu[d] * (n / d) * (n / d + 1) / 2 for d in range(1, b + 1)) +
            sum((Merten(n / m) - Merten(n / (m + 1))) * m * (m + 1) / 2 for m in range(1, n / (b + 
                1) + 1)))
# Recursive calculation of S(510510, N)
def S(N, i = 0):
    if N < 1: return 0
    if N == 1: return reduce(lambda x, y: x * y, [p - 1 for p in P[i:]])
    if i == len(P): return sum_euler_phi(N)
    if i < len(P):
        return (P[i] - 1) * S(N, i + 1) + S(N / P[i], i)

print(S(10**11))
