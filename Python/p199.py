from math import sqrt
import sys


def get_k4(k1, k2, k3):
    return k1 + k2 + k3 + 2 * sqrt(k1 * k2 + k2 * k3 + k3 * k1)


def solve():
    k = 1 + 2 / sqrt(3)
    uncovered_area = 1 - 3 * (1 / k) ** 2
    stack = [(-1, k, k), (k, -1, k), (k, k, -1), (k, k, k)]
    for i in range(11):
        next_stack = []
        for k1, k2, k3 in stack:
            k4 = get_k4(k1, k2, k3)
            next_stack += [(k1, k2, k4), (k2, k3, k4), (k3, k1, k4)]
            uncovered_area -= (1 / k4) ** 2
        stack = next_stack
        print(uncovered_area)


class Problem:
    pass


def main():
    problem = Problem()
    solve()


if __name__ == '__main__':
    sys.exit(main())