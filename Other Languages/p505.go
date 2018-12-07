package main

import "fmt"

func main() {
	fmt.Printf("A(10^12) = %d\n", A(1000000000000))
}

func A(n uint64) uint64 {
	return flip(negamax(n, 1, 0, (1<<60)-1, false))
}

func flip(n uint64) uint64 {
	return (1 << 60) - 1 - n
}

func x(n uint64) uint64 {
	var x uint64 = 0
	var y uint64 = 1
	var nn uint64 = (n << 1) + 1
	var main bool = false
	var mask uint64 = (1 << 60) - 1

	for nn != (1 << 63) {
		if main {
			if nn&(1<<63) != 0 {
				y, x = (2*y+3*x)&mask, y
			} else {
				y, x = (3*y+2*x)&mask, y
			}
		}
		if nn&(1<<63) != 0 {
			main = true
		}
		nn = nn << 1
	}
	return y
}

func negamax(n uint64, k uint64, alpha uint64, beta uint64, side bool) uint64 {
	if k >= n {
		return flip(x(k))
	}

	var bestv uint64 = 0
	var v uint64
	var a uint64 = alpha
	var b uint64 = beta

	// Potential problem
	v = flip(negamax(n, 2*k, flip(b), flip(a), !side))
	if v > bestv {
		bestv = v
	}
	if v > a {
		a = v
	}
	if b > a {
		v = flip(negamax(n, 2*k+1, flip(b), flip(a), !side))
		if v > bestv {
			bestv = v
		}
	}
	return bestv
}
