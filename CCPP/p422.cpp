/*
Linear transformation to y^(-2) - x^(-2) = 1 and calculated on it
X = (0, 1)
P1 = (15/8, 17/8)
P2 = (-5/12, -13/12)

Inverse transformation is
| x | = | -1 7 | | x |
| y |   | 7 1  | | y |

I got the recurrence formula by pencil/paper
{ x_(n+2) = x_n . y_(n+1) - x_(n+1) . y_n
{ y_(n+2) = y_(n+1) . y_n - x_(n+1) . x

but couldn't find the general solution so I brute forced it.
We need to calculate Pn for n = 830545249, because the cycle is 1000000008
*/

#include <iostream>
using namespace std;

typedef long long ll;

int main(int argc, char const *argv[]) {
	const ll M = 1000000007;
	const ll IM2 = 500000004;
	const ll IM24 = 41666667;
	ll a0 = 15, b0 = 17, c0 = 8;
	ll a1 = -5, b1 = -13, c1 = 12;

	for (ll i = 3; ; i++) {
		ll a = (a0 * b1 - a1 * b0) % M * IM2 % M;
		ll b = (b0 * b1 - a0 * a1) % M * IM2 % M;
		ll c = c0 * c1 % M * IM2 % M;
		if (a < 0)
			a += M;
		if (b < 0)
			b += M;
		a0 = a1, b0 = b1, c0 = c1;
		a1 = a, b1 = b, c1 = c;

		if (i == 830545249) {
			cout << ((7 * b - a) % M * IM24 % M + c * IM24 % M + (7*a+b) % M * IM2%M + c*IM2%M) % M << endl;
			break;
		}
	}

	return 0;
}
