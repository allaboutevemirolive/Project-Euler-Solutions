#include <cstdio>
#include <cmath>

double calc(int nn) {
    double t, a, b, x, y, x0, y0, step;
    double x1, x2, y1, y2, x20, y20, dx;
    double v, dv;

    a = 1; b = 3;
    v = t = 0;
    x0 = a * cos(t);
    y0 = b * sin(t);
    x20 = x0 + 1;
    y20 = 0;
    step = M_PI / nn;
    for (t = step; t <= M_PI + 1e-9; t += step) {
        x = a * cos(t);
        y = b * sin(t);
        x1 = -a * sin(t);
        y1 = b * cos(t);
        if (x > 0) dx = 1 / sqrt(x1 * x1 / (y1 * y1) + 1);
        else dx = 1 / -sqrt(x1 * x1 / (y1 * y1) + 1);
        y2 = y - (x1 / y1) * dx;

        x2 = x + dx;
        dv = -(x2 - x20) * (y2 + y20) * (y2 + y20) / 4;
        v += dv;
        x0 = x;
        y0 = y;
        x20 = x2;
        y20 = y2;
    }
    return (v - 4.0 / 3.0 * a * b * b) * M_PI;
}

int main() {
    int i;
    double v;

    for (i = 16; i < 10000000; i *= 2) {
        v = calc(i);
        printf("%d;%12.8f\n", i, v);
    }

    return 0;
}