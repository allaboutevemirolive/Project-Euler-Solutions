def f(n, b):
    return n ** 3 + b

def f_gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def f_diophantine(a, b, c):
    q, r = divmod(a, b)

    if r == 0:
        return 0, c // b
    else:
        u, v = f_diophantine(b, r, c)
        return v, u - q * v

def f_gcd_max(a, b):
    n_max = 0
    g_max = 1

    p0 = a ** 6 + 27 * b ** 2
    q0 = 8 * a ** 5
    r0 = 4 * a ** 3 * (a ** 3 + 3 * b)

    g0 = f_gcd(p0, q0)

    p1 = p0 // g0
    q1 = q0 // g0
    r1 = r0 // g0

    m0, n0 = f_diophantine(p1, -q1, r1)

    k1 = 0
    k0 = n0 // p1

    while k1 < a:
        n1 = n0 - k0 * p1
        g_tmp = f_gcd(f(n1 + a, b), f(n1, b))

        if g_tmp > g_max:
            g_max = g_tmp
            n_max = n1
        
        k1 += 1
        k0 -= 1

    return n_max

def f_gcd_sum(a, b):
    s = 0
    for i in range(1, a + 1):
        for j in range(1, b + 1):
            s += f_gcd_max(i, j)
    print(s)

def main():
    start = time.time()
    f_gcd_sum(18, 1900)
    print(time.time() - start)
    return

if __name__ == '__main__':
    main()