fac :: Integer -> Integer
fac n 
    | n < 0     = error "Negative arg"
    | n == 0    = 1
    | otherwise = n * fac (n - 1)

digits :: Integer -> [Integer]
digits n
    | n < 0     = error "Negative arg"
    | n < 10    = [n]
    | otherwise = digits (div n 10) ++ digits (rem n 10)

mySum :: [Integer] -> Integer
mySum []        = 0
mySum [x]       = x
mySum (x:xs)    = x + mySum xs

answer :: Integer
answer = mySum (digits (fac 100))
