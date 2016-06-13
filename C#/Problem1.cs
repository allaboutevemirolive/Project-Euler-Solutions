public void solve() {
	result = DivisibleBy(3, 999) + DivisibleBy(5, 999) - DivisibleBy(15, 999);
}

private int DivisibleBy(int n, int p) {
	return n * (p / n) * ((p / n) + 1) / 2;
}