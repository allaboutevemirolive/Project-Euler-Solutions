import Math.NumberTheory.Moduli ( powerMod )
import Math.NumberTheory.Primes.Sieve ( sieveFrom )

main = let x = 10^9; y = 10^7; n = 10^15::Int in print $
    sum $ map (a n) $ takeWhile (<=(x + y)) $ sieveFrom x
    where
        f (u, v, w) (x, y, _) = (mod (u * x + 13 * v * y) w, mod (u * y + v * x) w, w)
        a n p = mod ((2 * (\(x, _, _) -> x) ((\t@(_, _, w) n->
            (\(_, v, _) -> v) $ until (\(i, _, _) -> i <= 0) (\(i, u, v) ->
            (div i 2, if odd i then f u v else u, f v v)) (n, (1, 0, w), t))
            (mod (div (11 * (p + 1)) 2) p, mod (div (3 * (p + 1)) 2) p, p) $
            powerMod 2 (n - 1) (p * p - 1)) - 5) * powerMod 6 (-1::Int) p) p
