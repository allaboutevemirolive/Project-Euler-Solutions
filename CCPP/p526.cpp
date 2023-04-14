/**
 * notes:
 * 
 * n+4 (mod 11)
 * 16 possibilities mod 720720
 * 
 * 9 perfect numbers with residue 315, 4724 (mod 5040)
 * 1. n + 0 = a
 * 2. n + 1 = 24b * 6b
 * 3. n + 2 = c
 * 4. n + 3 = 2d * 4d
 * 5. n + 4 = 315 * e
 * 6. n + 5 = 4f * 2f
 * 7. n + 6 = g
 * 8. n + 7 = 6h * 24h
 * 9. n + 8 = i
 * 
 * abcdefghi are prime numbers
 * n = 2201 (mod 90090)
 * n = 4721 (mod 90090)
 * n = 11651 (mod 90090)
 * n = 71501 (mod 90090)
 * n = 78431 (mod 90090)
 * n = 85361 (mod 90090)
 * n = 87881 (mod 90090)
 * 
 * step 1: filter prime to 10^8
 * step 2: filter all numbers with all primes backwards in flag[100000000] at 16 possibilities
 * step 3: calculate perfect squares and perfect sequences
 * step 3.1: use crt for valid residues of n+4 (mod 720720 = 2^4 * 3^2 * 5 * 7 * 11 * 13):
 * * 272475, 55755, 191835, 469035, 161595, 438795, 715995, 358155
 * * 362565, 145845, 281925, 559125, 251685, 528885, 85365, 448245
 * step 4: bruteforce with residue + perfect sequences 
 * 
 * maybe can save time with statistical primality test vs sieve for primes up to sqrt(n)
*/

using namespace std;

#include <iostream>
#include <vector>

typedef long long int lli;

lli reduc[100];
lli ans[100];

lli invert(lli num, lli base) {
    reduc[0] = base;
    reduc[1] = num;
    ans[0] = 0;
    ans[1] = 1;

    int curr = 1;
    while (reduc[curr] != 1) {
        lli div = reduc[curr-1] / reduc[curr];
        reduc[curr+1] = reduc[curr-1] - div * reduc[curr];
        ans[curr+1] = ans[curr-1] - div * ans[curr];
        ++curr;
    }

    return (ans[curr] + base) % base;
}

// chinese remainder thm
lli crt(lli p1, lli r1, lli p2, lli r2) {
    lli k = r1 + ((p1-1) * r2) % p1;
    k = (k * invert(p2, p1)) % p1;
    
    return ((k*p2 + r2) % (p1 % p2));
}

int main() {
    vector<lli> rems, newrems;

    // 1 or 7 mod 16
    rems.push_back(1);
    rems.push_back(7);
    lli prod = 16;

    // 5 mod 9
    for (int i = 0; i < 2; ++i)
        rems[i] = crt(9, 5, prod, rems[i]);
    prod *= 9;

    // 1 mod 5
    for (int i = 0; i < 2; ++i) 
        rems[i] = crt(5, 1, prod, rems[i]);
    prod *= 5;

    // 3 mod 7
    for (int i = 0; i < 2; ++i) 
        rems[i] = crt(7, 3, prod, rems[i]);
    prod *= 7;

    // 1 to 4 mod 13
    newrems.clear();
    for (int i = 0; i < 4; ++i)
        for (int j = 1; j < 5; ++j)
            newrems.push_back(crt(13, j, prod, rems[i]));
    
    rems = newrems;
    prod *= 13;

    // sieve
    int* prime = new int[100000000];
    for (int i = 0; i < 100000000; ++i)
        prime[i] = 1;

    prime[0] = 0;
    prime[1] = 0;

    for (int i = 2; i < 10000; ++i) {
        if (prime[i]) {
            for (int goUp = i + i; goUp < 100000000; goUp += i) {
                prime[goUp] = 0;
            }
        }
    }

    // cache inverse primes
    for (int i = 15; i < 100000000; ++i) {
        if (prime[i]) {
            prime[i] = invert(prod, i);
        }
    }

    unsigned char* flag = new unsigned char[100000000];
    for (int i = 0; i < 100000000; ++i)
        flag[i] = 255;

    lli start = 10000000000000000;
    start = prod * (start / prod);

    for (unsigned int r = 0; r < rems.size(); ++r) {
        for (lli p = 15; p < 100000000; ++p) {
            if (!prime[p])
                continue;
            lli m = prime[p];
            lli base = (((start + rems[r]) % p) * m) % p;

            for (int i = 0; i < 9; ++i) {
                for (lli k = base; k < 100000000; k += p)
                    flag[k] = r;
                base = (base+m) % p;
            }
        }

        for (lli i = 0; i < 100000000; ++i) {
            if (flag[i] == r)
                continue;
            lli cand = start + rems[r] - prod * i;
            
            cout << cand << "    ";
            
            lli sum = 0;

            for (lli j = cand; j < cand + 9; ++j) {
                lli cp = j;
                for (lli p = 2; p < 8; ++p) {
                    while (!(cp % p))
                        cp /= p;
                }

                cout << j / cp << " ";
                sum += cp;
            }

            cout << "    " << sum << endl;
        }
    }

}