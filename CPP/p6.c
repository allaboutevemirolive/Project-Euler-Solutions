#include <stdio.h>
#define square(x) (x) * (x)

double difference(double n) {
    register double soq =  0;
    register double i;
    for (i = 1; i <= n; i++)
        soq += square(i);

    return square((n * (n + 1.0) / 2.0)) - soq;
}

int main() {
    printf("%.1f\n", difference(100.0));

    return 0;
}