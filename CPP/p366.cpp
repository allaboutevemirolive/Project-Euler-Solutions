#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>
#include <list>
using namespace std;
#define ll long long
#define MOD 100000000

ll fibonacci[92];
ll maxFibNumber(ll start, ll end) {
    ll max = -1;
    for (int i = 1; i <= 91; i++) {
        if (fibonacci[i] >= start && fibonacci[i] <= end) {
            max = fibonacci[i];
        }
    }

    return max;
}

ll sum(ll x) {
    if (x % 2 == 0)
        return (((x / 2) % MOD) * ((x + 1) % MOD)) % MOD;
    else
        return ((x % MOD) * (((x + 1) / 2) % MOD)) % MOD;
}

ll find(ll postojump, ll maxjump, ll start, ll end) {
    if (start > end) {
        return 0;
    }

    ll step = (maxjump - 1) / 2 - (start - postojump);
    step = min(end - start, step);

    ll nextpostojump = postojump + maxFibNumber(start - postojump, start + step - postojump);

    ll nextmaxjump = maxFibNumber(start - postojump, start + step - postojump);

    ll answer = (start % MOD - postojump % MOD) * ((step + 1) % MOD) % MOD;

    answer += sum(step);

    return answer + find(nextpostojump, nextmaxjump, start + step + 1, end);
}

int main() {

    fibonacci[0] = 1;
    fibonacci[1] = 1;
    for (int i = 2; i <= 91; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    ll low = 1;
    ll high = 1000000000000000000ll;
    ll totalValue = 0;

    for (int i = 2; i <= 91; i++) {
        totalValue = (totalValue + find(fibonacci[i], fibonacci[i], fibonacci[i] + 1, min(high, fibonacci[i + 1] - 1))) % MOD;
    }

    printf("%lld\n", totalValue);
    return 0;
}