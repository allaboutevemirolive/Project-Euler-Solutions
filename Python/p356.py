from gmpy2 import mpz
from math import floor

base = 2147483645.4141948

product = floor(pow(mpz(base), 987654321)) % 10**8
print(product)
