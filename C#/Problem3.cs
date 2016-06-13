const long num = 600851475143;
long newnum = num;
long largestFactorial = 0;

int i = 2;
while (i * i <= newnum) {
	if (newnum % i == 0) {
		newnum = newnum / i;
		largestFactorial = i;
	} else {
		i++;
	}
}

// Remainder is a prime number
if (newnum > largestFactorial) {
	largestFactorial = newnum;
}