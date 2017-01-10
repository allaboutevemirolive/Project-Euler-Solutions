

import sys


class facTable():
    def get(self, sieve_range):
        table = [{} for _ in range(sieve_range + 1)]
        for i in range(2, sieve_range + 1):
            if not table[i]:
                for j in range(i, sieve_range + 1, i):
                    table[j][i] = 1
                prime_power = i ** 2
                while prime_power <= sieve_range:
                    for j in range(prime_power, sieve_range + 1, prime_power):
                        table[j][i] += 1
                    prime_power = prime_power * i
        return table


class P320():
    def __init__(self):
        self.minFactorial_cached = {}

    def solve(self):
        print(self.get(1000000))

    def get(self, u):
        ans = 0
        table = facTable().get(u)
        facFactorisation = {}
        minFactorial = {}
        for i in range(1, u + 1):
            currentMinFact = 1
            for factor in table[i]:
                if factor not in facFactorisation:
                    facFactorisation[factor] = 0
                facFactorisation[factor] += table[i][factor]
                x = self.get_minFactorial(factor, facFactorisation[factor] * 1234567890)
                minFactorial[factor] = x
            if i < 10:
                continue
            currentMinFact = 1
            for divisor in facFactorisation:
                currentMinFact = max(currentMinFact, minFactorial[divisor])
            ans += currentMinFact
            if i % 1000 == 0:
                #print("S(" + i + ") = ", ans)
                #print(i, ans)
                print("S(", i, ") = ", ans)
        return ans

    def get_minFactorial(self, divisor, power):
        if power == 1:
            return divisor
        hashed = self.hash_pair(divisor, power)
        if hashed in self.minFactorial_cached:
            return self.minFactorial_cached[hashed]
        L = divisor * power // 2
        U = divisor * power
        while L <= U:
            M = (L + U) // 2
            count = self.get_divisor_count(M, divisor)
            if count < power:
                L = M + 1
            elif count >= power:
                U = M - 1
        assert (self.get_divisor_count(L, divisor) >= power)
        assert (self.get_divisor_count(L - 1, divisor) < power)
        self.minFactorial_cached[hashed] = L
        return L

    def get_divisor_count(self, n, divisor):
        ans = 0
        divisor_power = divisor
        while divisor_power <= n:
            ans += n // divisor_power
            divisor_power *= divisor
        return ans

    def hash_pair(self, x, y):
        return '''%d-%d''' % (x, y)


def main():
    p320 = P320()
    p320.solve()


if __name__ == '__main__':
    sys.exit(main())