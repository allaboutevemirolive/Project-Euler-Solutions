package main
import "fmt"
import "time"

const N = 12344321
const MOD = 135707531

func mod(k, m int) int {
	t := k % m
	if t < 0 {
		return t + m
	} else {
		return t
	}
}

func powerMod(base, n, m int) int {
	t := powerModAux(base, n, m)
	if t < 0 {
		return t + m
	} else {
		return t
	}
}

func powerModAux(base, n, m int) int {
	if n == 0 {
		return 1
	}
	if n == 1 {
		return base
	}
	halfn := powerModAux(base, n/2, m)
	if n %2 == 0 {
		return (halfn * halfn) % m
	} else {
		return (((halfn * halfn) % m) * base) % m
	}
}

func extendedGCD(a, b int) (int, int, int) {
	x, y, u, v := 0, 1, 1, 0
	for ;a != 0; {
		q, r = b / a, b % a
		m, n := x - u * q, y - v * q
		b, a, x, y, u, v = a, r, u, v, m, n
	}
	return b, x, y
}

func main() {
	s := 0
	a := N
	
	for k := 2; k <= N - 2; k++ {
		a = a * (k - 1) % MOD * (N - k + 1) % MOD * invMod(k, M) % M
		s += a * powerMod(N - k - 1, N - k, MOD) % MOD
	}
	s += N * (N - 1) % MOD * powerMod(N - 2, N - 1, MOD) % MOD
	s = mod(s, MOD)

	fmt.Printf("%d\n", s)
}