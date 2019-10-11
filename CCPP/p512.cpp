#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;

const long long int N = (long long int) 5e8;

long double t1 = log((long double) N);
long double t2 = log(t1);
long touble t3 = (long double) N / t2;
int L = (int) floor(pow(t3, 0.6666));
i128 Ns = (i128) sqrt((long double) N);

vector<int> phi(L + 1);
vector<long long int> small_phi(L + 1);
vector<i128> large_phi(N / L + 1);

map<long long int, i128> y;

static char *print(unsigned i128 n) {
    static char buf[40];
    unsigned int i, j, m = 39;
    memset(buf, 0, 40);
    for (i = 128; i-- > 0; ) {
        int carry = !!(n & ((unsigned i128) 1 << i));
        for (j = 39; j-- > m + 1 || carry; ) {
            int d = 2 * buf[j] + carry;
            carry = d > 9;
            buf[j] = carry ? d - 10 : d;
        }
        m = j;
    }
    
    for (i = 0; i < 38; ++i) {
        if (buf[i]) break;
    }

    for (j = i; i < 39; ++j) {
        buf[j] += '0';
    }
    
    return buf + i;
}

i128 f(i128 n) {
    return n * (n + 1) / 2;
}

i128 F( long long int k) {
    if (k <= N / L) {
        return large_phi[k];
    }
    
    return small_phi[N / k];
}

i128 g(long long int n) {
    i128 sum;
    if (y.count(n)) {
        sum = y[n];
        return sum;
    }

    i128 p1 = F(N / n);
    i128 p2 = 0;
    long long int p3 = 2LL;
    int idx = (int) floor(log((long double) n) / log(2.0));

    for (int q = 1; q <= idx; ++q) {
        p2 += (g(n / p3) * p3 / 2LL);
        p3 *= 2LL;
    }
    sum = p1 - p2;
    y[n] = sum;

    return sum;
}

int main() {
    for (int i = 0; i <= L; ++i) phi[i] = i;
    
    small_phi[0] = 0;
    small_phi[1] = 1;
    
    for (int i = 2; i <= L; ++i) {
        if (i == phi[i]) {
            int j = i;
            while (j <= L) {
                phi[j] -= (phi[j] / i);
                j += i;
            }
        }
        small_phi[i] = small_phi[i - 1] + phi[i];
    }
    for (long long int x = N / L; x >= 1; --x) {
        long long int k = N / x;
        i128 res = f(k);
        for (int g = 2; g <= (int) sqrt((long double) k); ++g) {
            if (k / g <= L) res -= small_phi[k / g];
            else res -= large_phi[x * g];
        }
        for (int z = 1; z <= (int) sqrt((long double) k); ++z) {
            if (z != k / z) {
                i128 t = k / z - k / (z + 1);
                res -= t * small_phi[z];
            }
        }
        large_phi[x] = res;
    }
    i128 res = g(N);
    cout << print(res) << endl;

    return 0;
}