mod = 10**9

res = 0
V = [0, 1, 0, 0, 0, 0]
for n in range(1, 10001):
    k = pow(10, n, mod)
    a = pow(3, n, mod)
    b = pow(6, n, mod)
    c = pow(9, n, mod)

    # measure distance from RHS of the room
    ra = k - a + 1
    rb = k - b + 1
    rc = k - c + 1

    # stumbling distance
    squares = [b * (b - 2) - a * (a - 2),
            c * (c - 2) - a * (a - 2),
            ra * (ra - 2) - rb * (rb - 2),
            c * (c - 2) - b * (b - 2),
            ra * (ra - 2) - rc * (rc - 2),
            rb * (rb - 2) - rc * (rc - 2)]

    res += (sum([V[i] * squares[i] for i in range(6)]) + squares[2])

    # update V
    V = [(V[1] + V[2]) % mod,
            (V[0] + V[3] + 1) % mod,
            (V[0] + V[4] + 1) % mod,
            (V[1] + V[5]) % mod,
            (V[2] + V[5]) %mod,
            (V[3] + V[4] + 1) % mod]

    print(res % mod)
