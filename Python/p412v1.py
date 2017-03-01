from kkmonleeUtils import EulerTools
import math

upperlim = 75000000
primes = EulerTools.primes_sieve(upperlim)
factor_dict = {}

# Compute how many of each prime factors are there in 75000000!
for p in primes:
    num_factors = 0
    q = p
    while upperlim // q > 0:
        num_factors += upperlim // q
        q *= p
    factor_dict[p] = num_factors

young_dict = {}

# Now count how many of each prime factor are the product
# of the Young tableau
index = 0
while primes[index] < 20000:
    p = primes[index]
    degree = 1
    young_dict[p] = 0
    while p ** degree < 20000:
        mult = 1
        while p ** degree * mult < 20000:
            if p ** degree * mult <= 5000:
                young_dict[p] += 2 * p ** degree * mult
            elif p ** degree * mult < 10000:
                young_dict[p] += 2 * (10000 - p ** degree * mult)
            elif 10000 < p ** degree * mult <= 15000:
                young_dict[p] += p ** degree * mult - 10000
            elif p ** degree * mult > 15000:
                young_dict[p] += 20000 - p ** degree * mult
            mult += 1
        degree += 1
    index += 1

answer = 1
for k in factor_dict.keys():
    if k in young_dict:
        mult = EulerTools.fast_exp(k, factor_dict[k] - young_dict[k], 76543217)
    else:
        mult = EulerTools.fast_exp(k, factor_dict[k], 76543217)
    answer *= mult
    answer = answer % 76543217

print(answer)
