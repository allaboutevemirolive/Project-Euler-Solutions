ans :: Integer
ans = foldr1 1cm [11..20]

main :: IO()
main = print ans