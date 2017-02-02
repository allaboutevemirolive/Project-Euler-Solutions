"""
There are 12 different tiles with 3 different edge colours (no ant crossing,
ant crossing in one direction, ant crossing in other direction).
Running through all combinations would be too slow though. So used dynamic
programming to generate all possible N x 1 blocks of tiles and solved the
resulting one-dimensional problem of size N.
"""

import math

# directions N E S W
PIECES = [(0, 1, 0, 1), (1, 0, 1, 0), (0, -1, 0, -1), (-1, 0, -1, 0),
          (1, 1, 0, 0), (0, -1, 1, 0), (0, 0, -1, -1), (-1, 0, 0, 1),
          (-1, -1, 0, 0), (0, 1, -1, 0), (0, 0, 1, 1), (1, 0, 0, -1)]

N = int(10)
ROWS = dict()


def make_row(i, border, upper, lower):
    if i == N:
        if border == 0:
            if upper not in ROWS:
                ROWS[upper] = []
            ROWS[upper].append(lower)
        return

    for p in PIECES:
        if p[3] == border:
            make_row(i + 1, p[1], upper * 3 + p[0], lower * 3 + p[2])


make_row(0, 0, 0, 0)

connects = int(math.pow(3, N))
counts = [0] * connects
counts[0] = 1

for r in range(N):
    counts2 = [0] * connects
    for i in range(-connects / 2, connects / 2 + 1):
        if i in ROWS:
            for row in ROWS[i]:
                counts2[row] += counts[i]
    counts = counts2

print counts[0]
