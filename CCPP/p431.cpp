#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

#define PI 3.14159265358979323846264338327950
#define alpha 2 * PI / 9
#define r 6
#define N 10000
#define dx PI / 2 / N

double f(double t, double x) {
    double temp = x * cos(t);
    temp = sqrt(r*r - x*x + temp*temp) + temp;
    return temp*temp*temp;
}

double intf(double x) {
    double ans = f(0, x) + f(PI, x);
    for (int i = 1; i < N; i++)
        ans += 2 * f(2*i*dx, x);
    for (int i = 1; i < 2*N; i += 2)
        ans += 4*f(i*dx, x);
    return tan(alpha)*2.*dx*ans/9;
}

int main() {
    double total = 0;
    // lower bounds
    double bds[6] = {1.6, 2.8, 3.6, 4.4, 5.1, 5.7};

    for (int i = 0; i < r; i++) {
        double goal = (20 + i) * (20 + i);
        double lbd = bds[i], ubd = lbd + .1;
        // bisection
        for (int iter = 0; iter < 40; iter++) {
            if (intf(.5*(lbd+ubd)) > goal)
                ubd = .5*(lbd+ubd);
        }
        total += .5 * (lbd + ubd);
    }
    cout << (long long) (total * 1e11) << endl;

    return 0;
}
