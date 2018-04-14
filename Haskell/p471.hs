g1 :: Integer -> Integer
g1 n = n * n `div` 2 * (n `div` 2 + 1) `div` 2 - n `div` 2 * (n `div` 2 + 1) * (n + 1) `div` 3

g2 :: Integer -> Float
g2 n = ((m^3 - 1) * log(m - 1) - m^3 * log(m / 2) - 15 * m^3 / 24 + m / 2 + m^2) / 3
    where m = fromInteger n

g :: Integer -> Float
g n = (fromInteger . g1 n) - g2 n