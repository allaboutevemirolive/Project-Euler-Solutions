#include <iostream>
using namespace std;

#define N 100000000
#define K 100000

int dv[N + 1], queue[N + 1];

int main() {
    for (int i = 1; i <= N; ++i)
        for (int j = i; j <= N; j += i)
            ++dv[j];
    
    long long s = 0;
    int p = 0, q = 0;
    
    for (int i = 1, j = 1; i <= N - K + 1; ++i) {
        const int r = i + K - 1;
        while (p < q && queue[p] < i) ++p;
        while (j <= r) {
            while (p < q && dv[j] > dv[queue[q - 1]]) --q;
            queue[q++] = j++;
        }
        s += dv[queue[p]];
    }
    cout << s << endl;

    return 0;
}