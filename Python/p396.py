def int_to_base(n, b):
    # returns list of digits, least significant digit is at position 0
    assert n >= 0
    assert b > 1
    if n == 0:
        return [0]

    res = []
    while n > 0:
        n, r = divmod(n, b)
        res += [r]

    return res

import sys
sysm.setrecursionlimit(2500) # unpacking powers of "f" goes deep

Mod = int(1e9) # since solution requires only last 9 digits

def f(n, k, p = 1):
    "fast-growing hierarchy function"
    assert n > 0
    assert k >= 0
    assert p > 0
    if p > 1:
        # unpack, f^3(n) = f(f(f(n)))
        return f(f(n, k, p - 1), k, 1)
    if k == 0:
        # f_0(n) = n + 1
        return (n + 1) % Mod

    # Handling k == 1 does not seem to improve speed
    # Handling k == 2 is a must because of module pow operation
    if k == 2:
        # f_2(n) = f_1^n(n) = 2 * 2 * 2 * ... * 2 * n = (2^n)^n
        return (pow(2, n, Mod) * n % Mod)

    # else if k > 0:
    # f_k+1(n) = f_k ^ n(n)
    return f(n, k - 1, n)

def goodstein_length(n):
    "returns length (mod 1e9) of Goodstein sequence for seed n"
    fval = 3
    for i, b in enumerate(int_to_base(n, 2)):
        if b == 1:
            fval = f(fval, i)

    return fval - 3

lengths = [goodstein_length(i) for i in range(1, 16)]
for i, l in enumerate(lengths):
    print "G(%s) = %s (mod %s)" % (i + 1, l, Mod)
print "Problem solution: %s" % (sum(lengths) % Mod)
