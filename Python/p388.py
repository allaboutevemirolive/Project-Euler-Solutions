"""
Let F(n) be the number of triples (a, b, c) with 1 <= a, b, c <= n and gcd(a, b, c) = 1,
and let G(n) be the number of couples (a, b) with 1 <= a, b <= n and gcd(a, b) = 1, then
D(n) = F(n) + 3G(n) + 3.

Computed F(n) and G(n) recursively using relations n^3 = sum F(floor(n / d)) from d = 1 to n,
and n^2 = sum G(floor(n / d)) from d = 1 to n.

The sums can be computed quite fast by cutting them, ie. when d < sqrt(n), sum over d,
then sum over the different values of k = floor(n / d).
"""

cacheF = {1: 1}

def F(n):
    if n in cacheF:
        return cacheF[n]
    else:
        s = n * n * n
        d = 2
        while ((n / d) ** 2) > n:
            s -= F(n / d)
            d += 1
        k = 1
        while k * k <= n:
            s -= F(k) * ((n / k) - (n / (k + 1)))
            k += 1
        cacheF[n] = s
        return s


cacheG = {1: 1}

def G(n):
    if n in cacheG:
        return cacheG[n]
    else:
        s = n * n
        d = 2
        while ((n / d) ** 2) > n:
            s -= G(n / d)
            d += 1
        k = 1
        while k * k <= n:
            s -= G(k) * ((n / k) - (n / (k + 1)))
            k += 1
        cacheG[n] = s
        return s


def D(n):
    return F(n) + 3 * G(n) + 3


print(D(10 ** 10))
