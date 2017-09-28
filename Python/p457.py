def modular_sqrt(a, p):
    """ Find a quadratic residue (mod p) of 'a'. p
        must be an odd prime.

        Solve the congruence of the form:
            x^2 = a (mod p)
        And returns x. Note that p - x is also a root.

        0 is returned is no square root exists for
        these a and p.

        The Tonelli-Shanks algorithm is used (except
        for some simple cases in which the solution
        is known from an identity). This algorithm
        runs in polynomial time (unless the
        generalized Riemann hypothesis is false).
    """
    # Simple cases
    #
    if legendre_symbol(a, p) != 1:
        return 0
    elif a == 0:
        return 0
    elif p == 2:
        return p
    elif p % 4 == 3:
        return pow(a, (p + 1) / 4, p)

    # Partition p-1 to s * 2^e for an odd s (i.e.
    # reduce all the powers of 2 from p-1)
    #
    s = p - 1
    e = 0
    while s % 2 == 0:
        s /= 2
        e += 1

    # Find some 'n' with a legendre symbol n|p = -1.
    # Shouldn't take long.
    #
    n = 2
    while legendre_symbol(n, p) != -1:
        n += 1

    # Here be dragons!
    # Read the paper "Square roots from 1; 24, 51,
    # 10 to Dan Shanks" by Ezra Brown for more
    # information
    #

    # x is a guess of the square root that gets better
    # with each iteration.
    # b is the "fudge factor" - by how much we're off
    # with the guess. The invariant x^2 = ab (mod p)
    # is maintained throughout the loop.
    # g is used for successive powers of n to update
    # both a and b
    # r is the exponent - decreases with each update
    #
    x = pow(a, (s + 1) / 2, p)
    b = pow(a, s, p)
    g = pow(n, s, p)
    r = e

    while True:
        t = b
        m = 0
        for m in xrange(r):
            if t == 1:
                break
            t = pow(t, 2, p)

        if m == 0:
            return x

        gs = pow(g, 2 ** (r - m - 1), p)
        g = (gs * gs) % p
        x = (x * gs) % p
        b = (b * g) % p
        r = m


def legendre_symbol(a, p):
    """ Compute the Legendre symbol a|p using
        Euler's criterion. p is a prime, a is
        relatively prime to p (if p divides
        a, then a|p = 0)

        Returns 1 if a has a square root modulo
        p, -1 otherwise.
    """
    ls = pow(a, (p - 1) / 2, p)
    return -1 if ls == p - 1 else ls

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    return x % m

import numpy
import sys

def primes_to_n(n):
    sieve = numpy.ones(n/3 + (n%6 == 2), dtype=numpy.bool)
    for i in xrange(1, int(n**0.5) / 3+1):
        if sieve[i]:
            k = 3*i+1 | 1
            sieve[k*k/3::2*k] = False
            sieve[k*(k-2*(i&1) + 4) / 3::2*k] = False
    return numpy.r_[2, 3, ((3*numpy.nonzero(sieve)[0][1:]+1)|1)]

primes = primes_to_n(10**7)

def f(n):
    return n*n-3*n-1

def R(p):
    if p==3:
        return 5

    s2=modular_sqrt(13,p)
    if s2==0:
        return 0
    if s2%2==0:
        s=(p+s2+3)/2
    else:
        s=(s2+3)/2

    if not s:
        return 0
    a1=(s-((s*s-3*s-1)*modinv(2*s-3,p*p)))%(p*p)
    a2=(p+3-s-((-1 + 3*p - 3*s - 2*p*s + s*s)*modinv(2*p+3-2*s,p*p)))%(p*p)
    if False:#a1>a2:
        print p,s,p+3-s,1,modinv(2*s-3,p),modinv(2*s-3,p*p)
        print p,s,p+3-s,2,modinv(2*s-3,p),modinv(2*s-3,p*p)
    
    return min(a1,a2)

def R1(p):
    s=0
    for j in xrange(p/2+1):
        if f(j)%p==0:
            s=j
    for x in xrange(0,(p*p)/2+p,p):
        for y in (s,p+3-s):
            if f(x+y)%(p*p)==0:
                #print x/p,x+y,y
                return x+y
    #print
    return 0

sum1=0
S1=0

for x in primes:
    if x<=S1:
        continue
    r=R(x)
    sum1+=r
    #if x%1000==73:
    #  print x,sum1
print sum1

