from fractions import gcd

sqrt = lambda x: pow(x, 0.5)
intsqrt = lambda x: int(sqrt(x))

def main():
    result = 0
    for a in range(1, intsqrt(intsqrt(n)) + 1):
        b_max = min(intsqrt(n) / a - a, a)
        for b in range(1, b_max + 1):
            if gcd(a, b) == 1:
                ra = (a * (a + b)) ** 2
                rb = (b * (a + b)) ** 2
                rc = (a * b) ** 2
                i = n / ra
                result += (i * (i + 1) / 2) * (ra + rb + rc)

    print(result)

if __name__ == '__main__':
    main(10 ** 9)