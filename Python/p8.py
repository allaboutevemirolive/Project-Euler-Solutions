from string import whitespace
from operator import mul

data = open('/tmp/data')
nos = [int(c) for line in data for c in line if c not in whitespace]
print max([reduce(mul, nos[i:i+5]) for i in range(len(nos) - 5)])
