#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;
typedef long double ld;
const int MAX_N = 200 + 10;

ld x[MAX_N];
int n;

ld calculate(ld a1, ld a2, ld a3) {
    return (cosl(a1) - cosl(a2)) * sinl(a2) + (cosl(a2) - cosl(a3)) * sinl(a3);
}

ld amt[MAX_N];

ld check(int i) {
    ld L = x[i - 1], R = x[i + 1];
    ld a1 = x[i - 1], a3 = x[i + 1];

    while (L + 1e-13 <= R) {
        ld M1 = (L * 2 + R) / 3, M2 = (L + R * 2) / 3;
        if (calculate(a1, M1, a3) < calculate(a1, M2, a3))
            R = M2;
        else
            L = M1;
    }

    return calculate(a1, x[i], a3) - calculate(a1, L, a3);
}

void improve(int i) {
    ld L = x[i - 1], R = x[i + 1];
    ld a1 = x[i - 1], a3 = x[i + 1];

    while (L + 1e-13 <= R) {
        ld M1 = (L * 2 + R) / 3, M2 = (L + R * 2) / 3;
        if (calculate(a1, M1, a3) < calculate(a1, M2, a3))
            R = M2;
        else
            L = M1;
    }
    x[i] = L;
}

ld eval() {
    ld ret = 0;
    for (int i = 1; i <= n + 1; ++i) {
        ret += (cosl(x[i - 1]) - cosl(x[i])) * sinl(x[i]);
    }

    return ret;
}

int main() {
    cin >> n;

    for (int i = 0; i <= n + 1; ++i) {
        x[i] = M_PI / 2 / (n + 1) * i;
    }

    for (int i = 1; i <= n; ++i) {
        amt[i] = check(i);
    }

    do {
        unsigned long who = max_element(amt + 1, amt + n + 1) - amt;
        if (amt[who] <= 1e-17)
            break;
        improve((int) who);
        if (who - 1 > 0)
            amt[who - 1] = check((int) (who - 1));
        if (who + 1 <= n)
            amt[who + 1] = check((int) (who + 1));
        amt[who] = 0;
    } while (true);

    printf("%.10lf\n", (double) eval() * 4);

    return 0;
}
