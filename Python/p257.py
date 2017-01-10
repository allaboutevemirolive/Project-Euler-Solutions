# Created by aa
# Project Euler 257

# ----------------- Algorithm -------------------------
# using Fool's method
# T_n searches with (nC2, 2(n - 2), n - 2, 2) so
# Eigenvalues are 2(n - 2) with multiplicity 1,
# n - 4  with multiplicity n - 1
# and -2 with multiplicity (n(n - 3))/2
# So number of triangles is one sixth of
# tr(A^3) = 8(n - 2)^3 + (n - 4)^3(n - 1) - 4n(n - 3)
# -------- OR ------------
# use my own method
# triangles in T_n come from either a triangle in K_n or from 3 edges
# meeting at a vertex
# therefore there must be nC3 + n(n-1C3) triangles


# both algorithm's simplify to (n - 2)(nCr) though...

# !!!! have a stupidity checker function to make sure big O complexity stays same

# ----------------- Algorithm -------------------------

import fractions
import math
import sys


class Problem():
    def solve(self):
        self.retard_check()
        for n in [100000000]:
            print(n, "ABC triangles =>", self.T(n))

    # just in case of a system buffer overflow
    # keep totient values here for now...
    def retard_check(self):
        assert (self.T(10) == 3)
        assert (self.T(100) == 46)
        assert (self.T(1000) == 610)
        assert (self.T(10000) == 7677)
        assert (self.T(100000) == 92318)

    # getter function
    def T(self, n):
        case_4bc_count = self.get_case_4bc_count(n)
        case_3bc_count = self.get_case_3bc_count(n)
        case_2bc_count = self.get_case_2bc_count(n)
        total_count = case_4bc_count + case_3bc_count + case_2bc_count
        return total_count

    # 3 BC sides and angle modder func
    def get_case_4bc_count(self, n):
        return n // 3

    # 3 BC sides modder func
    def get_case_3bc_count(self, n):
        different_parity_count = self.get_case_3bc_different_parity_count(n)
        same_parity_count = self.get_case_3bc_same_parity_count(n)
        return different_parity_count + same_parity_count

    def get_case_3bc_different_parity_count(self, n): # could make this function to static...
        p_bound = int(math.sqrt(n + 1) - 2)
        count = 0
        for p in range(1, p_bound + 1):
            if p % 3 == 0:
                continue
            q0 = p // 3 + 1
            if p % 2 == q0 % 2:
                q0 += 1
            for q in range(q0, p, 2):
                perimeter = (p + q) * (p + 3 * q)
                if perimeter > n:
                    break
                if fractions.gcd(p, q) > 1:
                    continue
                count += n // perimeter
        return count

    def get_case_3bc_same_parity_count(self, n): # might be static too
        m = 2 * n
        p_bound = int(math.sqrt(m + 1) - 2)
        count = 0
        for p in range(1, p_bound + 1, 2):
            if p % 3 == 0:
                continue
            q0 = p // 3 + 1
            if p % 2 != q0 % 2:
                q0 += 1
            for q in range(q0, p, 2):
                perimeter = (p + q) * (p + 3 * q)
                if perimeter > m:
                    break
                if fractions.gcd(p, q) > 1:
                    continue
                count += m // perimeter
        return count

    def get_case_2bc_count(self, n): #might be static or a global def
        p_bound = int((math.sqrt(4 * n + 1) - 3) / 2)
        count = 0
        for p in range(1, p_bound + 1, 2):
            for q in range(p // 2 + 1, p):
                perimeter = (p + q) * (p + 2 * q)
                if perimeter > n:
                    break
                if fractions.gcd(p, q) > 1:
                    continue
                count += n // perimeter
        return count


def main():
    problem = Problem()
    problem.solve()


if __name__ == '__main__':
    sys.exit(main())
