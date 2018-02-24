import Control.Monad
import Primes

result = do
    a <- [1..10000 - 1]
    let b = sumFactors a - a
    guard (b <= 10000 - 1)
    guard (a < b)
    let a' = sumFactors b - b
    guard (a == a')
    return (a, b)

isPrime n (x:xs) = (x*x > n) || (mod n x /= 0) && (isPrime n xs)
primes = 2 : filter (\x -> isPrime x primes) [3..]
sumFactors n = product $ map (\x -> let p = head x; r = length x in (p^(r+1) - 1) `div` (p - 1)) $ group $ factors n primes
