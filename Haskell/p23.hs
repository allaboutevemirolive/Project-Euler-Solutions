import Array
import List

main = print . sum $ filter (not . test) [1..28123]
test n = or [(abundant ! a) && (abundant ! (n - a)) | a <- [1..div n 2]]
abundant = listArray (0, max) $ map isAbundant [0..max] where max = 18123
isAbundant n = n < (sum $ divisors n)
divisors n = 1 : (nub $ facs ++ (map (div n) . reverse) facs) where facs = filter ((== 0) . mod n) [2..sqrt n]
sqrt' n = (floor . sqrt . fromIntegral) n