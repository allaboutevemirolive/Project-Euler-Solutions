# For abcde: let u = a - e, v = b - d
# x = base

# u > v = 0: abbbc, aaaab, abbbb
# s += 20*(u-1)*(x-u)
# s += 10*(x-u)

# u = v > 0: aabcc, aabbb, aaabb
#s += 30*(u-1)*(x-u)
#s += 20*(x-u)

# u > v > 0:
#s += 120*(v-1)*(u-v-1)*(x-u)  # abcde
#s += 120*(v-1)*(x-u) #aabcd, abcdd
#s += 120*(u-v-1)*(x-u) #abbcd, abccd
#s += 60*(x-u) #aabbc, abbcc
#s += 40*(x-u) #abbcd, abccd

from time import clock
time1 = clock()

# S(15) = 5274369
# S(111) = 400668930299

N = 100  # Answer: 134856101687520261
N = 300  # Answer: 552506775824935461
D = 10**18

base = None

def next_uv(u, v):
    global base
    # Consider the digits uv000 - 000vu:
    # If v > 0: (u, v-1, base-1, base-1-v, base-u)
    # If v == 0: (u-1, base-1, base-1, base-1, base-u)
    if v == 0:
        uu, vv = base - u, u - 1
        if vv > uu:
            uu, vv = vv, uu
        return uu, vv

    d0 = base - u
    d1 = base - 1 - v
    d2 = v - 1
    d3 = u
    if d1 < d0:
        d1, d0 = d0, d1
    if d2 < d0:
        d2, d0 = d0, d2
    if d2 < d1:
        d2, d1 = d1, d2
    if d3 < d1:
        d3, d1 = d1, d3
    if d3 < d2:
        d3, d2 = d2, d3
    return (base - 1 - d0, d3 - d1)

def S(x):
    global base
    base = x
    counts = []
    for u in range(x):
        counts.append((u+1)*[None])
    counts[0][0] = 0

    for u0 in range(x):
        for v0 in range(u0+1):
            if counts[u0][v0] is not None:
                continue
            cnt = 1
            chain = []
            u, v = u0, v0
            while True:
                chain.append((u, v))
                if u == 0:
                    break
                uu, vv = next_uv(u, v)
                if uu == u and vv == v:
                    break
                c = counts[uu][vv]
                if c is not None:
                    cnt += c
                    break
                u, v = uu, vv
                cnt += 1
            c = cnt
            for u, v in chain:
                counts[u][v] = c
                c -= 1

    s = -1 # for kaprekar itself

    for u in range(1, x):
        m = 10*(x-u)
        s += m*(2*u-1)*counts[u][0]
        s += m*(3*u-1)*counts[u][u]
        for v in range(1, u):
            s += m*(12*v*(u-v) - 2)*counts[u][v]
    return s

'''
print(S(15))
print(S(111))
'''

total = 0
for k in range(2, N+1):
    s = S(6*k+3)
    print(k, s)
    total += s

print(total % D)

time2 = clock()
print("N = {0:d} Time = {1:.1f}".format(N, time2 - time1))
