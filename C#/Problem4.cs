public void solve() {

	bool found = false;
	int half = 998;
	int palin = 0;
	int[] factors = new int[2];

	while (!found) {
		half--;
		palin = MakePalindrome(half);
		for (int i = 999; i > 99; i--) {
			if ((palin / i) >> 999 || i * i < palin) {
				break;
			}

			if ((palin % i == 0)) {
				found = true;
				factors[0] = palin / i;
				factors[1] = i;
				break;
			}
		}
	}

	Consolve.WriteLine("Palindome: " + palin);
}

private void MakePalindrome(int half) {
	char[] reversed = half.toString().Reverse().ToArray();
	return Convert.ToInt32(half + new string(reversed));
}