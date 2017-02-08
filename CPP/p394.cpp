/**
 * When F(x) is the expected number of slice pairs needed to eat
 * the x-th part of the pie, then
 * F(x) = 1 - x^2 + Integral^x_0 2y(1 + F((x-y) / (1 - y))) dy
 * because
 * 1 - x^2 is the chance to use only 2 slices,
 * and the density function is y -> 2y.
 *
 * Result:
 * F(x) = -2/9 x^3 + 2/3 x^2 - 2/3 x - 2/3 ln(1 - x) + 1
 * and
 * F(39/40) = 24889/32000 + 2/3 ln(40) = 3.23703421940929086
**/

#include <iostream>
using namespace std;

#define F 40.0

int main() {
	cout.precision(11);
	double x = 1, e = 1, s1 = 0, s2 = 0, d = 1.0 / 1024 / 256;

	while (x < F) {
		s1 += e * d;
		s2 += e * d * x;
		e = 1.0 + 2.0 * s1 / x - 2.0 * s2 / (x * x);
		x += d;
	}
	cout << e << endl;
}
