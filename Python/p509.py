def solve(n, mod):
    s = 0
    nims = dict()
    i, p = 0, 1
    while True:
        d = (n // p + 1) // 2
        if d == 0:
            break
        
        nims[i] = d

        i, p = i + 1, 2 * p

    for a in nims.keys():
        for b in nims.keys():
            c = a^b
            if no (c in nims.keys()):
                continue
            s += nims[a] * nims[b] * nims[c]
    
    return (n ** 3 - s) % mod

print(solve(123456787654321, 1234567890))