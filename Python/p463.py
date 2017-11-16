"""
if i is even S(floor(n / 2))
if i is odd T(n)
	T(2n) = T(n - 1) and
	T(4n + 1) = T(4n - 1) + f(4n + 1)

f(4n + 1) + f(4n + 3) = 5f(2n + 1) - 3f(n)

T(4n + 3) = T(2n + 1) * 5 - S(n) * 3 - 1

f(1) + f(3) = 4
5f(1) - 3f(0) = 5
"""

def f(n):
	if n == 1 or n == 3: return n
	elif n % 2 == 0:
		return f(n >> 1)
	elif n % 4 == 1:
		return f(n + 1 >> 1) * 2 - f(n >> 2)
	else:
		return f(n >> 1) * 3 - f(n >> 2) * 2

def S(n):
	if n <= 2: return n
	return S(n >> 1) + T(n + n % 2 - 1)

def T(n):
	if n == 1: return 1
	if n % 4 == 1:
		return T(n - 2) + f(n)
	else:
		return T(n >> 1) * 5 - S(n >> 2) * 3 - 1

print(S(3**37))
