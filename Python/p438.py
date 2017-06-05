from math import factorial

N = 7

pow2N = 2 ** N

numbits = [0, 1]
while len(numbits) < 2 * pow2N:
    numbits += [c + 1 for c in numbits]


def multiply(v, a):
    return [v[x] * (x - a) for x in range(N + 1)]


def crosses(v, h):
    cnt = 0
    for x in range(N):
        if v[x] < h < v[x+1] or v[x+1] < h < v[x]:
            cnt += 1
    return cnt


def value_2(v):
    n = len(v) - 1
    p2 = 0
    c = (n + 1) * (n + 2) // 2
    for x in range(n + 1):
        p2 += v[x] * c
        c *= (x + 2) * (n - x) / (-(x + 1) * (x + 3))
    return round(p2)


def sum_abs_coeff(y, v):
    q2 = value_2(v)
    p2 = 1
    for a in range(N):
        if not (v[a] < -1 < v[a + 1] or v[a + 1] < -1 < v[a]):
            p2 *= (-2 - a)
    if q2 + 1 < 0 < q2 + y - 1:
        s = ((q2 + 1) * q2 + (q2 + y - 1) * (q2 + y)) // 2
    else:
        s = abs(q2 + 1 + q2 + y - 1) * (y - 1) // 2
    return s * abs(p2) - (y - 1)


def make_all_products():
    products = []
    for n in range(N + 1):
        products.append([])

    for bits1 in range(1, 2 * pow2N):
        for bits2 in range(pow2N // 2):
            bits2 <<= 1
            if bits1 | bits2 != bits1:
                continue
            n = numbits[bits1] + numbits[bits2]
            if n > N:
                continue
            v = (N + 1) * [1]
            a = 0
            b1, b2 = bits1, bits2
            while b1 != 0:
                if b1 & 1 != 0:
                    v = multiply(v, a)
                if b2 & 1 != 0:
                    v = multiply(v, a)
                a += 1
                b1 >>= 1
                b2 >>= 1
            products[n].append(v)
    return products


def make_all_parabolas():
    parabolas = []
    for a1 in range(N - 2):
        for a2 in range(a1 + 3, N + 1):
            v = [(x - a1) * (x - a2) for x in range(N + 1)]
            y = a2 - a1 - 1
            parabolas.append((y, v))
    return parabolas


count = 1
totalsum = factorial(N + 1) - 1

products = make_all_products()
parabolas = make_all_parabolas()
for y, v in parabolas:
    count += y - 1
    totalsum += sum_abs_coeff(y, v)

no_int_roots = []

for n in range(N + 1):
    no_int_roots.append([])
no_int_roots[2] = parabolas

for n in range(3, N + 1):
    print("n = ", n)
    for k in range(2, n):
        for y, v in no_int_roots[k]:
            for u in products[n - k]:
                for z in range(1, y):
                    w = [u[x] * (v[x] + z) for x in range(N + 1)]
                    zeroes = crosses(w, -1)
                    if zeroes < n:
                        continue
                    yy = -max(h for h in w if h < 0)
                    count += yy - 1
                    totalsum += sum_abs_coeff(yy, w)
                    if n < N:
                        no_int_roots[n].append((yy, w))
    for w in products[n]:
        zeroes = crosses(w, -1)
        if zeroes < n:
            continue
        yy = -max(h for h in w if h < 0)
        count += yy - 1
        totalsum += sum_abs_coeff(yy, w)
        if n < N:
            no_int_roots[n].append((yy, w))

print(count, totalsum)
