L = 1000000
M = 100000007

F, I = [1, 1], [1, 1]

for n in 2..L / 2
	F << F[-1] * n % M
	I << M / n  - I[M % n] % M
end

y = s = 0
z = mn = p2 = 1

(L / 2 - 1).downto 0 do |x|
	s = (s + p2 * F[y + z] * F[x + y] * F[x + y + 1] * mn * (1 + (z&1))) % M
	mn = mn * x % M
	if z == 0
		z = 2
		mn *= I[x + y]
	else
		z -= 1
		y += 1
		p2 = p2 * 2 % M
		mn *= I[y]
	end
end
p s