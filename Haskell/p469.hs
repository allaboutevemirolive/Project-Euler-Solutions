import Text.Printf ( printf )

main = printf "%.14f\n" (exp (-2) / 2 + 0.5 :: Double)
