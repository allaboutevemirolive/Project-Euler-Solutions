import Math.NumberTheory.Powers(powerMod)

main = let n = 10^6;
m = 10^9 + 7 in print $ flip mod m $ sum $ map (\k -> let
    q = 1 - k * k in mod q m * (1 - powerMod q n m) * powerMod k (-2::Int) m) [1..n]