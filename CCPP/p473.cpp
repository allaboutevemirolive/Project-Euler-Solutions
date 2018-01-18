#include <cstdio>

typedef long long ll;

#define N 60

ll F[N] = {0, 1};

ll f(int n) {
    if (n >= 0) return F[n];
    return (n & 2 ? 1 : -1) * F[-n];
}

void compute() {
    int k = 20;
    for (int mask = 0; mask < (1 << k); mask += 2) {
        bool bad = false;
        for (int i = 1; i < k; ++i)
            if ((mask & 1 << i) && (mask & 1 << (i - 1)))
                bad = true;
        if (bad) continue;
        
        ll s0 = 0, s1 = 0;

        for (int i = 0; i < k; ++i) {
            if (mask & 1 << i) {
                s0 += f(i) + f(-i - 1);
                s1 += f(i - 1) + f(-i - 2);
            }
        }

        if (s0 == 0) {
            for (int i = 0; i < k; ++i)
                putchar(mask & 1 << i ? '1' : '0');
            printf(" %lld\n", s1);
        }
    }
}

ll sglob, nglob;

void recurse(int k, ll s) {
    sglob += s;
    for (int j = k; ; j += 2) {
        ll news = F[j - 1] + F[j + 5] + s;
        if (news > nglob) break;
        recurse(j + 6, news);
    }
}

ll calculate_sum(ll n) {
    nglob = n, sglob = 1;
    recurse(2, 0);
    recurse(4, 2);
    return sglob;
}

int main() {
    for (int n = 2; n < N; ++n)
        F[n] = F[n - 1] + F[n - 2];
    compute();
    printf("%lld\n", calculate_sum(10000000000LL));
    
    return 0;
}
