from math import log, factorial

N, K = 10**14, 20

gamma = 0.5772156649015328606065120900824024310421

def S(k, n):
    return (log(n) - sum(1 / j for j in range(1, k + 1)) + gamma) / factorial(k)

sk = str(S(K, N))
e = sk.find('e')
mantissa = round(float(sk[:e]), 9)
exponent = int(sk[e + 1:]) + round(log(N, 10)) * K

print(str(mantissa) + 'e' + str(exponent))