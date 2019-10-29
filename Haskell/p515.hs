import System.Environment(getArgs)
import Math.NumberTheory.Primes
import Math.NumberTheory.Moduli

solve [a, b, k] = sum [ z | p <- [a .. a + b - 1], isPrime p, Just z <- [invertMod (k - 1) p] ]

main = getArgs >>= print.solve.map read