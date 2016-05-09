key = putStrLn (show sum)
sum = sum [x | x <- [-0..999], (mod x 5) == 0 || (mod x 3) == 0]
