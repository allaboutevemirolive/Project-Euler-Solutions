isDivisibleBy :: Integer -> Integer -> Bool
m `isDivisibleBy` n = 0 == m `mod` n

primes :: [Integer]
primes = filterPrimes [2..] where
    filterPrimes :: [Integer] -> [Integer]
    filterPrimes (x:xs) = x : filterPrimes (filter (not . (`isDivisibleBy` x)) xs)

isqrt :: Integer -> Integer
isqrt = floor . sqrt . fromIntegral

candidatePrimeFactors :: Integer -> [Integer]
candidatePrimeFactors x = takeWhile (<= s) primes where
    s = isqrt x

isPrime :: Integer -> Bool
isPrime x | x < 2 = False
isPrime x = isEmpty $ filter (x `isDivisibleBy`) $ candidatePrimeFactors x where
    isEmpty [] = True
    isEmpty _ = False

solve :: Integer
solve = sum $ filter isPrime [2..2000000]