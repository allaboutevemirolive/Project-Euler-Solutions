#include <stdio.h>
#include <string.h>
#include <math.h>
typedef long long ll;
#define N 5000000

char primes[N+1];
char mu[N+1];

ll calculate(int val) {
    int max = (int) floor(sqrt(val));
    int x, y;
    ll result1 = 0, result2 = 0;
    for (x = 2; x <= max; x++)
        for (y = 1; y < x; y++) {
            ll tmp1 = val / (x + y);
            int low, high, delta, z;
            ll period_sum = 0;
            ll maxk;
            result1 += tmp1 * (tmp1 - 1) / 2;
            delta = val - tmp1 * x;
            high = delta / x;
            maxk = high / y;
            for (z = 1; z <= y; z++)
                period_sum += (delta - x * z) / y;
            result1 += maxk * period_sum - x * y * maxk * (maxk - 1) / 2;
            for (z = y * maxk + 1; z <= high; z++) 
                result1 += (delta - x * z) / y;
            if (tmp1 <= max) {
                result2 += tmp1 * (tmp1 - 1) / 2;
                high = max - tmp1;
                maxk = high / y;
                result2 += maxk * period_sum - x * y * maxk * (maxk - 1) / 2;
                for (z = y * maxk + 1; z <= high; z++)
                    result2 += (delta - x * z) / y;
            } else {
                result2 += max * (max - 1) / 2;
            }
        }
    return 2 * result1 - result2;
}

int main() {
    int x, y, d;
    ll result, prev;
    memset(primes, 1, sizeof(primes));
    for (x = 2; x * x <= N; x++)
        if (primes[x])
            for (y = x * x; y <= N; y += x)
                primes[y] = 0;
    memset(mu, 1, sizeof(mu));
    for (x = 2; x * x <= N; x++)
        if (primes[x]) {
            for (y = x; y <= N; y += x)
                mu[y] = -mu[y];
            for (y = x * x; y <= N; y += x * x)
                mu[y] = 0;
        }

    for ( ; x <= N; x++ )
        if (primes[x])
            for (y = x; y <= N; y += x)
                mu[y] = -mu[y];

    result = (3ll * N / 2 - 2) * N / 2;
    x = 0;
    prev = 0;
    for (d = 1; d <= N; d++)
        if (mu[d]) {
            int div = N / d;
            if (div != x) {
                x = div;
                prev = calculate(div);
                if (!prev)
                    break;
            }
            result += 2 * mu[d] * prev;
        }
    printf("%lld\n", 2 * result + N * (N + 1ll) / 2);

    return 0;
}
