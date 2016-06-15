ans :: Integer
solution = (sum [1..100]) ^ 2 - sum [x ^ 2 | x <- [1..100]]

main :: IO()
main = print ans