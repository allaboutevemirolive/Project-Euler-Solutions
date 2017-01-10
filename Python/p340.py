import sys

class Foo():
    def get(self, n, a, b, c):
        if n > b:
            return n - c
        delta = 1 - 4 * a + 3 * c
        delta_pos, in_delta_pos = divmod(b - n, a)

        return b - c + 1 - (delta_pos + 1) * delta - in_delta_pos - (a - 1) * delta_pos

    def get_sum(self, a, b, c):
        gayNums = (b + 1) // a
        gayDelta = self.get(b - a, a, b, c) - self.get(b, a, b, c)

        gayStartPos = b - a + 1
        gayEndPos = b
        gayStartVal = self.get(gayStartPos, a, b, c)
        gayEndVal = self.get(gayEndPos, a, b, c)
        gayPartSum = (gayStartVal + gayEndVal) * a // 2
        gaySum = (2 * gayPartSum + gayDelta * (gayNums - 1) * a) * gayNums // 2

        endStartPos = 0
        endEndPos = b - a * gayNums
        endBeginVal = self.get(endStartPos, a, b, c)
        endEndVal = self.get(endEndPos, a, b, c)
        endSum = (endBeginVal + endEndVal) * (endEndPos - endStartPos + 1) // 2

        return endSum + gaySum

class Problem():
    def solve(self):
        self.check()
        self.get()

    def get(self):
        function = Foo()
        result = function.get_sum(21**7,7**21, 12**7)
        print(result, result % 10**9)

    def check(self):
        function = Foo()
        assert(function.get(0, 50, 2000, 40) == 3240)
        assert(function.get(2000, 50, 2000, 40) == 2040)
        assert(function.get_sum(50, 2000, 40) == 5204240)

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())