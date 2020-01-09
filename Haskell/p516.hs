smooth5 :: Integer -> [Integer]
smooth5 lim = sort $ [a*b*c] a<-takeWhile (<=lim) $ iterate (*2) 1, b<-takeWhile (<= (lim `div` a)) $ iterate (*3) 1, c<-takeWhile (<=(lim `div` (a*b))) $ iterate (*5) 1]

primesHigh :: Integer -> [Integer]
primesHigh lim = dropWhile (<6) $ filter isPrime $ map (+1) $ smooth5 lim

p516' :: Integer -> Integer
p516' lim = process 1 $ primesHigh lim where
    sm = smooth5 lim
    process i [] = force $ i*(sum $ takeWhile (<=(lim `div` i)) sm)
    process i (a:as)
        | i*a > lim = process i []
        | otherwise = force $ process i as + process (i*a) as

p516 = p516' (10^12) `mod` (2^32)