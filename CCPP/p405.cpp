#include <iostream>
using namespace std;

const unsigned long long int modulo = 410338673; // 17^7
const unsigned long long int phi = 386201104; // 16 * 17^6
const unsigned long long int inverse = 355626850; // inverse of 15

unsigned long long int represent() {
    const unsigned long long int exponent = 1e18;
    unsigned long long int ret = 1;
    unsigned long long int pow = 10;

    for (unsigned long long int bits = 1; bits <= exponent; bits <<= 1) {
        if (exponent & bits) {
            ret *= pow;
            ret %= phi;
        }
        pow *= pow;
        pow %= phi;
    }

    return ret;
}

unsigned long long int calculate(unsigned long long int i) {
    i %= phi;
    unsigned long long int pow = 2;
    unsigned long long int ret = 1;

    for (unsigned long long int bits = 1; bits <= i; bits <<= 1) {
        if (i & bits) {
            ret *= pow;
            ret %= modulo;
        }
        pow *= pow;
        pow %= modulo;
    }
    ret = 14 + ret * ((6 * ret - 20 + modulo) % modulo);
    ret %= modulo;

    return (ret * inverse) % modulo;
}

int main() {
    cout << calculate(represent()) << endl;

    return 0;
}
