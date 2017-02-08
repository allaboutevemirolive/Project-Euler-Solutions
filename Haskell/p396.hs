sum1to7 = sum $ map goodstein [1..7]

goodstein n | n >= 8 = error "Too large!"
goodstein n = go 2 (toBinary n)
  where
    go k [] = k - 2
    go k xs = k `seq` go (k + 1) (decrement (k + 1) xs)

-- convert number to a list of bits, LSB first
toBinary 0 = []
toBinary n = let (q, r) = divMod n 2 in r : toBinary q

decrement b [x] = if x > 1
  then [x -1]
  else []

decrement b (x:xs) = if x > 0
  then (x - 1) : xs
  else (b - 1) : decrement b xs
