/*
 * Probability of not flipping k is:
 * p_k = ((k - 1)^2 + (N - k)^2) / N^2
 *
 * If it's white at the end then the number of flips must be even so...
 * P_k = Mc0(1-p_k)^M + Mc2(1-p_k)^(M-2)p^2_k + ...
 *
 * Which looks like the binomial theorem for [(1-p_k) + p_k]^M which has
 * both odd and even terms. But if we look at [(1-p_k) + p_k]^M instead
 * it will have the odd terms with opposing sign. So if we add these two
 * together the odd terms will cancel out so...
 * P_k = 1/2(1 + (1 - 2p_k)^M)
 *
 * Remains to sum P_k from k = 1, ..., N. M is fairly big so that when
 * 2p_k is even slightly bigger than (1-2p_k)^M is basically 0. So we
 * sum P_k for k close to 1 or N only and approximate P_k ~ 1 for the middle
 * terms. For me 1e8 for close enough.
 *
 * Basically exploiting the symmetry of P_k = P_(N+1-k) to sum from both sides
 * at once. Also I take the "1" term out of the P_k and just add it on at the end.
 */

#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

int main() {
    ll N = 1e10;
    double N2 = (double) N*N;
    double M = 4000;

    double total = 0;

    for (double k = 1; k <= 1e8; k++)
        total += pow(1 - (4*k*(N+1-k) - 2) / (N2), M);

    cout << (ll) ((total + N/2)*1e3) << endl;
}
