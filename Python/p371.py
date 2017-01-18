import sys


class Problem:
    def solve(self):
        status = [[0.0] for _ in range(999)]
        status[0] = [1.0]
        transitionMatrix = self.transitionMatrix()
        expectedValue = 0.0

        for i in range(1, 301):
            status[998] = [0.0]
            status = self.multiply(transitionMatrix, status)
            expectedValue += status[998][0] * i
            print("Expected value =>", expectedValue, "\n status[998][0] =>", status[998][0], "\n i =>", i)
        print("expected value =>", expectedValue)

    def transitionMatrix(self):
        m = [[0.0 for _ in range(999)] for _ in range(999)]
        for i in range(499):
            m[i][i] = (i + 1) / 1000
            if i < 498:
                m[i + 1][i] = (1000 - 2 * i - 2) / 1000
            m[499 + i][i] = 1 / 1000
            m[998][i] = i / 1000
        for i in range(499, 998):
            m[i][i] = (i - 499 + 1) / 1000
            if i < 997:
                m[i + 1][i] = (1000 - 2 * (i - 499) - 2) / 1000
            m[998][i] = (i - 499 + 1) / 1000
        m[998][998] = 1.0

        return m

    def multiply(self, x, y):
        rv = [[0 for j in range(len(y[0]))] for i in range(len(x))]
        for i in range(len(x)):
            for j in range(len(y[0])):
                for k in range(len(y)):
                    rv[i][j] += x[i][k] * y[k][j]
        return rv


def main():
    problem = Problem()
    problem.solve()


if __name__ == "__main__":
    sys.exit(main())
