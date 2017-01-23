from math import pi, cos, log10, frexp, fmod

def C(m, n):
	cm, cn = pi / m, pi / n
	p = 1.0
	p2 = 0

	for a in range(m):
		for b in range(n):
			if a or b:
				p *= 2.0 * (2.0 - cos(a * cm) - cos(b * cn))
				while p < 0.5:
					p *= 2.0
					p2 -= 1
				while p >= 2.0:
					p /= 2.0
					p2 += 1
	return p / (m * n), p2

m, e = C(100, 500)
# converting powers of 2 to powers of 10
man, exp = frexp(m)
man, exp = 2 * man, (exp + e - 1) * log10(2)
man *= 10 ** fmod(exp, 1)

print(str(round(man, 4)) + 'e' + str(int(exp)))