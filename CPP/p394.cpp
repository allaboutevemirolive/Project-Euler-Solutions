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
