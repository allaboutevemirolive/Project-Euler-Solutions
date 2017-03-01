import Control.Monad (guard)

floorSqrt :: Int -> Int
floorSqrt = floor . sqrt . fromIntegral

triplesUnder :: Int -> [(Int, Int, Int)]
triplesUnder lim = do
    -- See Ivan Niven, Herbert S. Zuckerman, Hugh L. Montgomery
    -- "An introduction to the theory of numbers", p. 231
    -- min ((s+1)^2-s^2) (2*(s+1)*s) <= lim
    -- min (2*s+1) (2*s^2 +2*s) <= lim
    -- s>=1 so the first is always smaller
    s <- [1..(lim - 1) `div` 2]
    -- min (r^2 - s^2) (2*r*s) <= lim
    r <- [s+1, s+3..max (lim `div` (2*s)) (floorSqrt (lim + s^2))]
    -- r>s, r+s odd, 2 * r * s <= lim OR r^2 - s^2 <= lim
    guard $ gcd r s == 1
    return (r^2 + s^2, r^2 - s^2, 2*r*s)

divs lim a b = (lim * (gcd a b)) `div` b

-- firstMatches: take a from the oddpart, t always even, s always even
firstMatches rlim alim (hypotpart, oddpart, evenpart) =
    (alim `div` oddpart) * (divs rlim hypotpart oddpart)

-- secondMatches: take a from the evenpart, t even, s even
secondMatches rlim alim (hypotpart, oddpart, evenpart) =
    (alim `div` evenpart) * (divs rlim hypotpart evenpart)

-- thirdMatches: take a from the evenpart, t odd, s odd
thirdMatches rlim alim (hypotpart, oddpart, evenpart) =
    let z = evenpart `div` 2 in
        ((alim `div` z) - (alim `div` evenpart)) *
            ((divs rlim hypotpart z) - (divs rlim hypotpart evenpart))

matchesForTriple :: Int -> Int -> (Int, Int, Int) -> Int
matchesForTriple rlim alim triple
    = sum $ map (\f -> f rlim alim triple) $ [firstMatches, secondMatches, thirdMatches]

slantMatches rlim alim = sum $ map (matchesForTriple rlim alim) $ triplesUnder (2*alim)

p410f rlim alim = 2*rlim*alim + 4*(slantMatches rlim alim)

--main = print $ p410f 10 100
main = do
    let sh =  p410f (10^9) (10^8)
    print sh
    let fh = p410f (10^8) (10^9)
    print fh
    print (fh + sh)
