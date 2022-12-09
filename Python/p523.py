cache = dict()

def solve(n, x):
    if n == x: return 0
    if (n, x) in cache:
        return cache[(n, x)]

    ans = 1
    for i in range(x):
        ans += solve(i + 1, i)
    cache[(n, x)] = ans
    
    return ans

def main():
    v = 30
    e = 0
    for s in range(1, v):
        add = 0
        for k in range(s + 1):
            add += solve(s, k)
        e += add * 1 ./ (s + 1)

    print(e)
