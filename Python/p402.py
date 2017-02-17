#   Looking at Df(0) = f(1)-f(0), D^2f(0), D^3f(0), D^4f(0) for f(n) = n^4 + an^3 + bn^2 + cn, we
#   find that M(a,b,c) can be computed as M(a,b,c) = gcd(1+a+b+c, 14+6a+2b, 6a+12, 24). In
#   particular it means that M(a,b,c) = M(a%24, b%24, c%24). The 24^3 possible values of this
#   function can be easily computed using the gcd formula.
#   This implies that S(24k) = S(24) * k^3, where S(24) turns out to be 27984. More generally,
#       S(N) = A*(N//24)^3 + B(N%24)*(N//24)^2 + C(N%24)*(N//24) + D(N%24)
#   The coefficients can be computed easily as A = S(24), D(x) = S(x), B(x) = (S(48+x) + S(x))/2 -
#   - S(24+x) - 3S(24), C(x) = 2[S(24+x) + S(24)] - [S(48+x) + 3S(x)]/2.
#   Fibonacci sequence mod 24 has a period of 24; thus we can consider it in the form Gj(t) =
#   F(24t + j), with each subsequence Gj having constant residue modulo 24 (call it gj). The
#   recurrence relation for Gj is:
#       Gj(t) = 103682*Gj(t-1) - Gj(t-2)
#       Rj(t) = 103682*Rj(t-1) - Rj(t-2) + 4320*gj,  where Rj(t) = Gj(t)//24
#   Thus, the j-th subsequence of the { S(F(k)) } can be written as
#       S(F(24t+j)) = A*Rj(t)^3 + Bj*Rj(t)^2 + Cj*Rj(t) + Dj
#   The starting values for Rj(t) are given by: Rj(0) = F(j)//24 and Rj(1) = F(j+24)//24. This
#   allows us to deduce Rj(-1) = 103682*Rj(0) - Rj(1) + 4320*gj.
#
#   Denote c = 103682 and fj = 4320gj = 4320(F(j) % 24). Then elements of S(F(24t+j)) can be
#   computed recursively as (index j is omitted below for brevity)
#       |1           |   |   1     0     0     0    0  0   0     0  0  0 | |1             |
#       |R(t)        |   |   f     c    -1     0    0  0   0     0  0  0 | |R(t-1)        |
#       |R(t-1)      |   |   0     1     0     0    0  0   0     0  0  0 | |R(t-2)        |
#       |R(t)^2      |   | f^2   2fc   -2f   c^2  -2c  1   0     0  0  0 | |R(t-1)^2      |
#       |R(t)R(t-1)  |   |   0     f     0     c   -1  0   0     0  0  0 | |R(t-1)R(t-2)  |
#       |R(t-1)^2    | = |   0     0     0     1    0  0   0     0  0  0 |*|R(t-2)^2      |
#       |R(t)^3      |   | f^3 3cf^2 -3f^2 3fc^2 -6fc 3f c^3 -3c^2 3c -1 | |R(t-1)^3      |
#       |R(t)^2R(t-1)|   |   0   f^2     0   2fc  -2f  0 c^2   -2c  1  0 | |R(t-1)^2R(t-2)|
#       |R(t)R(t-1)^2|   |   0     0     0     f    0  0   c    -1  0  0 | |R(t-1)R(t-2)^2|
#       |R(t-1)^3    |   |   0     0     0     0    0  0   1     0  0  0 | |R(t-1)^3      |
#   Denote the LHS vector as Vj(t), and the transition matrix Pj. Initial conditions are given by
#       Vj(0) = (1, rj, uj, rj^2, rj*uj, uj^2, rj^3, rj^2*uj, rj*uj^2, uj^3)'
#   with rj = F(j)//24 and uj = fj + c*rj - F(24+j)//24. We also denote
#       SIGj(T) = (1, Sum[Vj(t)|0<=t<=T]')'
#   This matrix satisfies initial equation SIGj(0) = (1, Vj(0)')', and the transition equation
#                 |    1    0 |             |    1    0 |^T
#       SIGj(T) = | Vj(0)  Pj |*SIGj(T-1) = | Vj(0)  Pj | * SIGj(0)
#   Finally, the sum of interest can be evaluated as Sum_j = (0,Dj,Cj,0,Bj,0,0,A,0,0,0)*SIGj(T)
#
#   Solution took 0.948 seconds.

K = 1234567890123
MOD = 10**9

# Fibonacci numbers
Fmem = {0:0, 1:1}
def F(n):
    if n not in Fmem:
        Fmem[n] = F(n - 1) + F(n - 2)
    return Fmem[n]

# M(a, b, c) and S(n) functions
# GCD
def gcd(x, y):
    while x:
        (x, y) = (y % x, x)
    return y

# Compute table of M-values
M = [[[gcd(gcd(1 + a + b + c, 24), gcd(14 + 6 * a + 2 * b, 6 * a + 12))
       for c in range(25)] for b in range(25)] for a in range(25)]

# Brute-force implementation of S() function
Smem = dict() # memoization storage
def S(n):
    if n not in Smem:
        Smem[n] = sum([M[a % 24][b % 24][c % 24]
                       for a in range(1, n + 1) for b in range(1, n + 1) for c in range(1, n + 1)])
    return Smem[n]

# Matrix manipulation
def identity(n):
    """ Returns an identity matrix of size n. """
    return [[int(x == y) for y in range(n)] for x in range(n)]

def mat_mod_multiply(A, B, M):
    """
    Return the product of two matrices A * B module M
    """
    nrows = len(A)      # number of rows in the resulting matrix
    ncols = len(B[0])   # number of columns in the resulting matrix
    nfold = len(B)      # folding dimension
    assert nfold == len(A[0]), "Matrix dimensions are non-conformable!"
    return [[sum([A[i][k] * B[k][j] % M for k in range(nfold)]) % M
             for j in range(ncols)] for i in range(nrows)]

def mat_mod_fold(A, b, M):
    """ Return the product of a matrix times a vector, module M """
    nrows = len(A)
    nfold = len(b)
    assert nfold == len(A[0]), "Matrix dimensions are non-conformable!"
    return [sum([A[i][k] * b[k] % M for k in range(nfold)]) % M for i in range(nrows)]

def mat_mod_power(A, n, M):
    """ Return matrix A raised to the power n, module M.
        A must be a square matrix """
    nrows = len(A)
    assert nrows == len(A[0]), "A must be a square matrix."
    res = identity(nrows)
    while n > 0:
        if n & 1:
            res = mat_mod_multiply(A, res, M)
        n >>= 1
        if n > 0:
            A = mat_mod_multiply(A, A, M)
    return res

answer = 0
for j in range(24):
    T = (K // 24) - (j > K % 24)
    if T < 0:
        continue
    c = 103682
    g = F(j) % 24
    f = g * (c - 2) / 24
    r0 = F(j) // 24
    rm1 = f + c * r0 - (F(24 + j) // 24)
    SIG0 = [1, 1, r0, rm1, r0**2, r0*rm1, rm1**2, r0**3, r0**2*rm1, r0*rm1**2, rm1**3]
    P = [[1,            0,        0,       0,        0,      0,   0,    0,       0,   0,  0],
         [1,            1,        0,       0,        0,      0,   0,    0,       0,   0,  0],
         [r0,           f,        c,      -1,        0,      0,   0,    0,       0,   0,  0],
         [rm1,          0,        1,       0,        0,      0,   0,    0,       0,   0,  0],
         [r0**2,     f**2,    2*f*c,    -2*f,     c**2,   -2*c,   1,    0,       0,   0,  0],
         [r0*rm1,       0,        f,       0,        c,     -1,   0,    0,       0,   0,  0],
         [rm1**2,       0,        0,       0,        1,      0,   0,    0,       0,   0,  0],
         [r0**3,     f**3, 3*c*f**2, -3*f**2, 3*f*c**2, -6*f*c, 3*f, c**3, -3*c**2, 3*c, -1],
         [r0**2*rm1,    0,     f**2,       0,    2*f*c,   -2*f,   0, c**2,    -2*c,   1,  0],
         [r0*rm1**2,    0,        0,       0,        f,      0,   0,    c,      -1,   0,  0],
         [rm1**3,       0,        0,       0,        0,      0,   0,    1,       0,   0,  0]]

    PT = mat_mod_power(P, T, MOD)
    SIGjT = mat_mod_fold(PT, SIG0, MOD)
    Aj = S(24)
    Bj = (S(48 + g) + S(g)) / 2 - S(24 + g) - 3 * S(24)
    Cj = 2 * (S(24 + g) + S(24)) - (S(48 + g) + 3 * S(g)) / 2
    Dj = S(g)
    answer += (Dj * SIGjT[1] + Cj * SIGjT[2] + Bj * SIGjT[4] + Aj * SIGjT[7]) % MOD
    print(".")

answer -= S(F(0)) + S(F(1))
print("\nAnswer = ", (answer % MOD))