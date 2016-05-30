from sympy import sqrt

def main():
    s = 600851475143

    while True:
        spf = smallPrime(s)
        if spf < s:
            s //= spf
        else:
            return str(s)

def smallPrime(n):
    assert n >= 2
    for i in range(2, sqrt(n) + 1):
        if n % i == 0:
            return i
    return n


if __name__ == "__main__":
    print(main())
