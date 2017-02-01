limit = 10 ** 10
bMax = int(limit ** (1.0 / 3)) + 1


def f(b, c, a, s=0):
    while 1:
        a, c = 2 * b * (b * b * c + b * a + c) + a, b * (2 * b * c + 2 * a) + c
        if a / 2 > limit: return s
        s += f(c, b, a) + f(c, -b, a) + a / 2


print sum(f(b, 0, b) for b in xrange(2, bMax, 2))
