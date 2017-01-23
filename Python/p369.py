import itertools
import sys


class Problem():
    def __init__(self):
        self.factorial = self.__init_factorial()
        self.patterns = self.__init_patterns()

    def __init_factorial(self):
        result = [1]
        d = 1
        for i in range(1, 13 + 1):
            d *= i
            result.append(d)

        return result

    def __init_patterns(self):
        result = {}
        for cardCount in range(1, 4 + 1):
            result[cardCount] = []
            for pattern in itertools.combinations(range(4), cardCount):
                result[cardCount].append([i in pattern for i in range(4)])
        return result

    def solve(self):
        count = 0
        for n in range(4, 13 + 1):
            count += self.get(n)
        print(count)

    def get(self, n):
        totalCount = 0
        for distribution in itertools.product(range(13 + 1), repeat=4):
            a, b, c, d = distribution
            if a + 2 * b + 3 * c + 4 * d == n and a + b + c + d >= 4:
                permutationCount = self.factorial[a + b + c + d] // self.factorial[a] // self.factorial[b] // \
                                   self.factorial[c] // self.factorial[d]
                distributionCount = 0

                unpacking = []
                for i in range(4):
                    unpacking += [self.patterns[(i + 1)] for j in range(distribution[i])]

                for XD in itertools.product(*unpacking):
                    badugiCount = self.getBadugiCount(XD)
                    distributionCount += badugiCount * permutationCount

                print(distribution, '=>', distributionCount)
                totalCount += distributionCount
        print(n, '=>', totalCount)
        return totalCount

    def getBadugiCount(self, hand):
        distribution = [[] for i in range(4)]
        current = 0
        for same in hand:
            for i in range(4):
                if same[i]:
                    distribution[i].append(current)
            current += 1
        for i in range(4):
            if not distribution[i]:
                return 0
        count = self.binomial(13, current)
        for fourthCard in itertools.product(*distribution):
            if len(set(fourthCard)) == 4:
                return count
        return 0

    def binomial(self, n, m):
        return self.factorial[n] // self.factorial[m] // self.factorial[n - m]


def main():
    problem = Problem()
    problem.solve()


if __name__ == "__main__":
    sys.exit(main())
