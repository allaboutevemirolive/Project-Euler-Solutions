def hi(t):
    # find 2**k such that 2**k <= t < 2**(k+1)
    h = 1
    while t > 1:
        h <<= 1
        t >>= 1
    return h

def g(t, c):
    h = hi(t)
    d = t - h
    if t == 1:
        return 0
    if d == 0:
        if c <= t // 2:
            return t * t // 4 + g(t // 2, c)
        else:
            return t * t // 2 + g(t, c - t // 2)
    elif c > h:
        return h * h + g(2 * h - d, c - h)
    elif c > h - d:
        return h * h + g(d, c + d - h)
    elif c <= d:
        return h * h // 2 + g(d, c)
    else:
        return h * h // 2 + g(2 * h - t, c)

F = [1, 1]
sum_gf = 0
for t in xrange(2, 46):
    F.append(F[-2] + F[-1])
    GF = g(F[t], F[t - 1])
    sum_gf += GF
print sum_gf