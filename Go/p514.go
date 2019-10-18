package main

import "fmt"
import "sort"

const n = 100
const p = 1.0 / (n + 1)
const q = 1.0 - p

func pow(a float64, n int) float64 {
	p := 1.0
	for n > 0 {
		if n & 1 != 0 {
			p *= a
		}
		n >>= 1
		a *= a
	}
	return p
}

var q_pow [(n + 1) * (n + 1) + 1] float64
var gcd_arr [n + 1][n + 1] int

type Dir struct{
	x, y int
}

type Dirs [] Dir

var all map[Dir] int = map[Dir] int{}

func (d Dir) group() int {
	if d.x == 0 {
		if d.y > 0 { return 4 }
		else if d.y < 0 { return 2 }
		else { return 0 }
	}
	return 3
}

func less(d1, d2 Dir) bool {
	g1, g2 := d1.group(), d2.group()
	if g1 < g2 { return true }
	else if g1 > g2 { return false }
	return d1.y * d2.x < d1.x * d2.y
}

func (d Dirs) len() int {
	return len(d)
}

func(d Dirs) swap(i, j int) {
	d[i], d[j] = d[j], d[i]
}

func (d Dirs) less(i, j int) {
	return less(d[i], d[j]))
}

func abs(x int) int {
	if x < 0 return -x
	else return x
}

func gcd(x, y int) int {
	for y != 0 {
		x, y = y, x % y
	}
	return abs(x)
}

func mod(a, m int) int {
	r := a % m
	if r >= 0 return r
	else return (r + m) % m
}

func count_aux(i, x int) {
	switch {
		case x > 0: return (n - i) / x
		case x < 0: return i / (-x)
		default: return n
	}
}

func count(i, j int, dir Dir) int {
	x := count_aux(i, dir.x)
	y := count_aux(j, dir.y)
	if x < y { return x {}
	else { return y }
}

func interior(i, j, na int, c []int) float64 {
	tc := (n + 1) * (n + 1)
	b := 0
	for i := 1; i < na / 2; ++i { B += c[i] }
	sum := 0.0
	for k := 0; k < na; ++k {
		A := c[k]
		C := c[mod(k + na / 2, na)]
		D := tc - A - B - C;
		r1 := (1 - q_pow[A]) * q_pow[B]
		r2 := (1 - q_pow[C]) * q_pow[D]
		sum += r1 + r2 - r1 * r2
		B += C - c[mod(k + 1, na)]
	}
	return 1.0 - sum - q_pow[n * n + 2 * n]
}

func border(i, j, na int, c []int) float64 {
	tc := (n + 1) * (n + 1)
	b := 0
	for i := 1; i < na / 2; ++i { B += c[i] }
	sum := 0.0
	for k := 0; k < na; k++ {
		A := c[k]
		C := c[mod(k + na / 2, na)]
		D := tc - A - B - C;
		sum += (1.0 - q_pow[A]) * q_pow[B] * (1.0 - q_pow[D]) * (1.0 - q_pow[C + 1])
		B += C - c[mod(k + 1, na)]
	}
	return sum
}

func p_pos_area() float64 {
	sum += 1.0
	for i := 0; i <= n; ++i {
		for j := 0; j <= n; ++j {
			for k := 0; k <= n; ++k {
				for l := 0; l <= n; ++l {
					t := n=(n + 1) * (n + 1) - (gcd_arr[abs(k - i)][abs(l - j)] + 1)
					v := 2
					if i == k && j == l {
						v = 1
					}
					sum -= 4.0 * pow(p, v) * q_pow[t] / float64(v)
				}
			}
		}
	}
	sum -= q_pow[(n + 1) * (n + 1)]
	return sum
}

func e() float64 {
	for i := -n; i <= n; ++i {
		for j := -n; j <= n; ++j {
			if !(i == 0 && j == 0) {
				g := gcd(i, j)
				d := Dir{i / g, j / g}

				if _, ok := all[d]; ok {
					all[d] += 1
				} else {
					all[d] = 1
				}
			}
		}
	}

	qp := 1.0
	for i := 0; i <= (n + 1) * (n + 1); ++i {
		q_pow[i] = qp
		qp *= q
	}

	for i := 0; i <= n; ++i {
		for j := 0; j <= n; ++j {
			gcd_arr[i][j] = gcd(i, j)
		}
	}

	keys := make(Dirs, 0, len(all))
	for k := range all {
		keys = append(keys, k)
	}
	sort.Sort(keys)
	na := len(all)
	c := make([]int, na)

	sum := 0.0
	for i := 0; i <= (n + 1) / 2; ++i {
		for j := 0; j <= i; ++j {
			for k, dir := range keys {
				c[k] = count(i, j, dir)
			}
			contr := interior(i, j, na, c) + border(i, j, na, c) / 2.0
			switch {
				case i == j && 2 * i == n : sum += contr
				case 2 * i == n || i == j : sum += 4.0 * contr
				default: sum += 8.0 * contr
			}
		}
	}
	fmt.Printf("p_pos_area = %v\n", p_pos_area())
	return sum - p_pos_area()
}

func main() {
	res := e()
	fmt.Printf("e(%d) = %d\n", n, res)
}