N = 100
MOD = 1000000033

# Binomial theorem (n, k)
binomial = [[1]]
for i in range(100):
    row = [1]
    for j in range(i):
        row.append((binomial[-1][j] + binomial[-1][j + 1]) % MOD)
    row.append(1)
    binomial.append(row)

# R(m, n) memoization
memo = [[-1 for j in range(N + 1)] for i in range(N + 1)]
for i in range(N + 1):
    if i == 1:
        memo[0][1] = 1
        memo[1][0] = 1
    else:
        memo[0][i] = 0
        memo[i][0] = 0

def R(m, n):
    if memo[m][n] != -1:
        return memo[m][n]
    ans = pow(2, m*n, MOD)
    for a in range(1, m + 1):
        for b in range(0, n + 1):
            if a == m and b == n:
                continue
            temp = (binomial[m - 1][a - 1] * binomial[n][b]) % MOD
            temp = (temp * pow(2, (m - a) * (n - b), MOD)) % MOD
            temp = (temp * R(a, b)) % MOD
            ans -= temp
    memo[m][n] = ans
    memo[n][m] = ans
    return ans

def main():
    ans = 0
    for m in range(1, N + 1):
        for n in range(1, N + 1):
            ans = (ans + R(m, n)) % MOD
    print(ans)
main()
