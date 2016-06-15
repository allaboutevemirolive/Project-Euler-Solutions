biggestDivisor :: Integer -> Integer
biggestDivisor n
				| even n = biggestDivisor (div n 2)
				| otherwise = m n 3
				where m n d
						| d >= n = d
						| mod n d == 0 = m (div n d) d
						| otherwise = m n (d + 2)

main :: IO()
main = print $ biggestDivisor 600851475143