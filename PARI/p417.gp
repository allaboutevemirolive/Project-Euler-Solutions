// run by entering p417(100000000) in GP

p417(maxn) = {
	local(s = 0, n, m);
	for (n = 3, maxn,
		m = n;
		while (m % 2 == 0, m /= 2);
		while (m % 5 == 0, m /= 5);
		if (m > 1, s += znorder(Mod(10, m)))
	);
	s
}
