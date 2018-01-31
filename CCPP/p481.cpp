#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<double> vd;

const int N = 14;
double E[1 << N][N];
double W[1 << N][N][N];

int next(int n, int mask, int i) {
    for (int k = i + 1; k < n; ++k)
        if (mask & 1 << k) return k;
    for (int k = 0; k <= i; ++k)
        if (mask & 1 << k) return k;
    return -1;
}

vd linear(const vd& a, const vd& b) {
    int n = (int) a.size();
    double A = 1.0, B = 0.0;

    for (int i = 0; i < n; ++i) {
        B += A * b[i];
        A *= a[i];
    }

    vd x(n);
    x[0] = B / (1.0 - A);
    
    for (int j = n - 1; j > 0; --j) {
        x[j] = a[j] * x[(j + 1) % n] + b[j];
    }
    return x;
}

double solve(vd S) {
    int n = (int) S.size();

    for (int mask = 1; mask < (1 << n); ++mask) {
        vi x;
        for (int i = 0; i < n; ++i)
            if (mask & 1 << i) x.push_back(i);
        int m = (int) x.size();

        if (m == 1) {
            int i0 = x[0];
            E[mask][i0] = 0.0;
            for (int i = 0; i < n; ++i) 
                W[mask][i0][i] = i == i0 ? 1.0 : 0.0;
            continue;
        }

        vi dead(m);

        for (int h = 0; h < m; ++h) {
            int i = x[h];
            double maxpr = -1.0;
            dead[h] = -1;
            
            for (int k = 1; k < m; ++k) {
                int j = x[(h + k) % m];
                int newmask = mask - (1 << j);
                double pr = W[newmask][next(n, newmask, i)][i];
                if (maxpr + 1e-12 < pr) {
                    maxpr = pr;
                    dead[h] = j;
                }
            }
        }

        // E[mask][i]
        vd a(m), b(m);
        for (int h = 0; h < m; ++h) {
            int i = x[h];
            a[h] = 1.0 - S[i];
            int newmask = mask - (1 << dead[h]);
            b[h] = 1.0 + S[i] * E[newmask][next(n, newmask, i)];
        }
        vd X = linear(a, b);
        for (int h = 0; h < m; ++h) {
            E[mask][x[h]] = X[h];
        }

        // W[mask][i][k] for all i and given k
        for (int l = 0; l < m; ++l) {
            int k = x[l];
            for (int h = 0; h < m; ++h) {
                int i = x[h];
                a[h] = 1.0 - S[i];
                int newmask = mask - (1 << dead[h]);
                b[h] = S[i] * W[newmask][next(n, newmask, i)][k];
            }
            vd X = linear(a, b);
            for (int h = 0; h < m; ++h)
                W[mask][x[h]][k] = X[h];
        }
    }
    return E[(1 << n) - 1][0];
}

int main() {
    int fib[16] = {0, 1};
    for (int k = 2; k <= 15; ++k) fib[k] = fib[k - 1] + fib[k - 2];
    int n = 14;
    vd S(n);
    for (int k = 1; k <= n; ++k)
        S[k - 1] = double(fib[k]) / fib[n + 1];
    printf("%.8lf\n", solve(S));
    return 0;
}