import Control.Monad (guard, liftM)

isPythagoreanTriplet :: Integer -> Integer -> Integer -> Bool
isPythagoreanTriplet a b c = a * a + b * b - c * c == 0

solve :: [Integer]
solve = do
    a <- [1..1000]
    b <- [a..(1000 - a)]
    let c = 1000 - a - b
    guard $ b <= c
    guard $ isPythagoreanTriplet a b c
    return $ product [a, b, c]