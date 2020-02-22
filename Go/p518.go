package main

import "fmt"
import "github.com/cznic/mathutil"

// Binary powering algorithm
func pow(a, b uint32) uint32 {
	var p uint32 = 1
	for b > 0 {
		if b&1 != 0 { p *= a }
		b >>= 1
		a *= a
	}
	
	return p
}

func f(a, b uint32, d uint64) uint32 {
	if !mathutil.IsPrime(b) { return 0 }
	var c uint32
	c = uint32(uint64(b + 1) * uint64(b + 1) / uint64(a + 1)) - 1
	if mathutil.IsPrime(c) && a < b && b < c {
		var sum uint32 = a + b + c
		fmt.Printf("(%d, %d, %d) = %d :: %d\n", a, b, c, sum, d)
		return sum
	} else {
		return 0
	}
}

func t2(n uint32) uint32 {
	var res uint32 = 1
	for _, f := range mathutil.FactorInt(n) {
		res *= pow(f.Prime, (f.Power + 1) / 2)
	}
	
	return res
}

func p518(n uint32) uint64 {
	var sum uint64 = 0
	var a, k uint32
	for a = 2; a <= n; a++ {
		if mathutil.IsPrime(a) {
			ta := t2(a + 1)
			for k = (a + 1) / ta + 1; uint64(k) * uint64(k) <= uint64(a + 1) * uint64(n) / uint64(ta) / uint64(ta); k++ {
				sum += uint64(f(a, ta * k - 1, sum))
			}
		}
	}

	return sum
}

func main() {
	// fmt.Printf("S(100) = %d\n", p518(100))
	fmt.Printf("S(100000000) = %d\n", p518(100000000))
}