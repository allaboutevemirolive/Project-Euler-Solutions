import time

START = time.time()

SIZE = 10**8
arr = [0] * (SIZE + 1)
sum = 0

for i in xrange(2, SIZE + 1):
    if i > SIZE / 2:
        break

    if arr[i] == -1:
        continue
    a = SIZE // i

    if arr[i] == 0:
        for j in xrange(2 * i, SIZE / 2, i):
            if arr[j] != -1:
                arr[j] += 1
        sum += a * (a - 1) / 2
    # when number is a square
    elif arr[i] == 1:
        for j in xrange(2 * i, SIZE / 2, i):
            arr[j] = -1
    # it has an odd number of factors
    elif arr[i] % 2 == 1:
        sum += a * (a - 1) / 2
    # prime divisors are even
    elif arr[i] % 2 == 0:
        sum -= a * (a - 1) / 2

print("Actual sum: ", sum * 6 + (SIZE - 2) * 6)
print("Time taken: ", time.time() - START)