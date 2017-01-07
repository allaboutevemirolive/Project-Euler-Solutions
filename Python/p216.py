import sys

def compute():
    LIMIT = 50000000
    sequence = [2 * i * i - 1 for i in range(LIMIT + 1)]
    sequence[0] = sequence[1] = -1

    ans = 0
    for (i, term) in enumerate(sequence):
        if i < 2:
            continue

        if term == 2 * i * i - 1:
            ans += 1

        if 1 < term <= LIMIT * 2:
            p = term

            for j in range(i + p, LIMIT + 1, p):
                while True:
                    sequence[j] //= p
                    if sequence[j] % p != 0:
                        break

            for j in range(i + (p - i) * 2 % p, LIMIT + 1, p):
                while True:
                    sequence[j] //= p
                    if sequence[j] % p != 0:
                        break

    return str(ans)

if __name__ == "__main__":
    print(compute())