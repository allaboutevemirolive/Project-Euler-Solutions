from functools import lru_cache

def f(h, k):
    return 3 if h == 0 else 2 if k == 1 or h == 1 else 1

@lru_cache(maxsize=None)
def count(c, h=0, m=10**9):
    if c <= 0:
        return int(c == 0)
    return sum(f(h, k) * count(c - k, k) for k in range(1, h + 2)) % m

N = 20000
for n in range(N):
    count(n)

print(count(N))