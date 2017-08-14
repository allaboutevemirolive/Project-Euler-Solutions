// #![feature(inclusive_range_syntax)]
use std::cmp::max;
use std::collections::HashMap;

const M: usize = 1_234_567_891;

struct Context {
    v: HashMap<(usize, usize, bool), usize>
}

fn f(c: &mut Context, m: usize, n: usize, is_exact: bool) -> usize {
    if is_exact {
        if n == 1 { return 1 }
        if m == 1 { return 1 }
        if m == 2 { return n }
    } else {
        if n == 1 { return m }
        if m == 1 { return 1 }
        if m == 2 { return n + 1 }
    }

    if c.v.contains_key(&(m, n, is_exact)) {
        return c.v[&(m, n, is_exact)]
    }

    let n1 = n / 2;
    let n2 = n - n1;

    let m0 = (m as f64).sqrt() as usize + 1;
    let sum = if !is_exact {
        (1..m0).fold(0, |a, k|
            (a + f(c, k, n1, true) * f(c, m/k, n2, is_exact)) % M)
        + (1..m0 + 2).fold(0, |a, i|
            (a + (f(c, max(m/i, m0), n1, false) + M - f(c, max(m / (i + 1), m0), n1, false)) * f(c, i, n2, false) % M) % M)
    } else {
        (1..m0).fold(0, |a, k|
            (
                a
                + if m % k == 0 && k * k <= m { (f(c, k, n1, true) * f(c, m/k, n2, true)) % M } else { 0 }
                + if m % k == 0 && k * k < m { (f(c, m/k, n1, true) * f(c, k, n2, true)) % M } else { 0 }
            ) % M
        )
    };

    c.v.insert((m, n, is_exact), sum % M);
    sum % M
}

fn main() {
    let c = &mut Context { v: HashMap::new() };
    println!("Result = {}", f(c, 1_000_000_000, 1_000_000_000, false));
}