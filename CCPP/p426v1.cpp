#include <iostream>
#include <vector>

using namespace std;

typedef uint64_t ull;
typedef int64_t ll;

inline ull max(ull a, ull b) {
	return a > b ? a : b;
}

// Makes all entries at least as large as the last one
void updateJumps(vector<ull> &jump, ll size) {
	ull j = 1;
	while (jump[size - j] < jump[size] and j <= size) {
		jump[size - j] = jump[size];
		j++;
	}
}

int main() {
	ull soq = 0;		// sum of squares
	unsigned int i = 0;
	ull s = 290797;
	ull balls;
	ull gap;
	ull limit = 10000000;
	vector<ull> ballsR;
	vector<ull> jump;
	ll size = -1;
	ll maxsize = 0;

	while (i <= limit) {
		balls = s % 64 + 1;
		s = (s * s) % 50515093;
		gap = s % 64 + 1;

		if (i == limit)
			gap = -1;

		if (balls > gap) {
			soq += gap*gap;
			ballsR.push_back(balls - gap);
			jump.push_back(gap);
			size++;
			maxsize = max(size, maxsize);
			updateJumps(jump, size);
		} else {
			soq += balls*balls;
			jump[size] = max(jump[size], balls);
			updateJumps(jump, size);
			ull gapR = gap - balls;

			while (gapR > 0 and size >= 0) {
				if (ballsR[size] > gapR) {
					soq -= (jump[size]) * (jump[size]);
					soq += (jump[size] + gapR) * (jump[size] + gapR);

					ballsR[size] -= gapR;
					jump[size] += gapR;
					updateJumps(jump, size);
					gapR = 0;
				} else {
					soq -= (jump[size]) * (jump[size]);
					soq += (jump[size] + ballsR[size]) * (jump[size] + ballsR[size]);
					jump[size - 1] = max(jump[size] + ballsR[size], jump[size - 1]);
					gapR -= ballsR[size];
					ballsR.erase(ballsR.end() - 1);
					jump.erase(jump.end() - 1);
					size--;
					updateJumps(jump, size);
				}
			}
		}
		i += 2;
		s = (s * s) % 50515093;
	}

	cout << "soq: " << soq << "\n\n";
	cout << "max array size:\t" << maxsize << endl;
}
