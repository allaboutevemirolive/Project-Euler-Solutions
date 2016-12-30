#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (1000035)
#define PRIME_COUNT (78500)

class p234 {
public:
    inline long long minimum(long long a, long long b) {
        return (a < b) ? a : b;
    }

    bool sieve_visited[SIEVE_RANGE] = {};
    long long primes[PRIME_COUNT] = {};

    void Sieve() {
        int currPos = 0;
        for (long long i = 2; i < SIEVE_RANGE; i++) {
            if (!sieve_visited[i]) {
                primes[currPos] = i;
                currPos++;

                for (long long j = i + i; j < SIEVE_RANGE; j += i) {
                    sieve_visited[j] = true;
                }
            }
        }
    }

    long long sumMultiple(long long divisor, long long start, long long end) {
        long long a = start;
        if (a % divisor) {
            a += divisor - (a % divisor);
        }
        long long n = end / divisor - (start - 1) / divisor;
        return n * (2 * a + (n - 1) * divisor) / 2;
    }

    void Solve(long long upperBound) {
        long long totalSum = 0;
        for (int i = 0; primes[i]*primes[i] <= upper_bound; i++)
        {
            long long start = primes[i] * primes[i] + 1;
            long long end = minimum(primes[i+1] * primes[i+1] - 1, upper_bound);
            total_sum += SumMultiple(primes[i], start, end)
                         + SumMultiple(primes[i+1], start, end)
                         - 2 * SumMultiple(primes[i]*primes[i+1], start, end);
        }
        std::cout << total_sum << std::endl;
    }

    int p234() {
        Sieve();
        Solve(999966663333);
        return 0;
    }
};


