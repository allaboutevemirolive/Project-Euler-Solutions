#include <stdio.h>

#define XMAX 21
#define YMAX 21

typedef long long int ll;

int main() {
    ll matrix[XMAX][YMAX];
    
    for (int i = 0; i <= XMAX - 1; i++) {
        matrix[XMAX - 1][i] = 1;
        matrix[i][YMAX - 1] = 1;
    }

    for (int i = XMAX - 2; i >= 0; i--) {
        for (int j = YMAX - 2; j >= 0; j--) {
            matrix[i][j] = matrix[i + 1][j] + matrix[i][j + 1];
        }
    }

    printf("%lld\n", matrix[0][0]);

    return 0;
}