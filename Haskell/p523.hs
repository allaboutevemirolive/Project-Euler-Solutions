factorial n =
    product [1..n]

totalSteps 3 = 9
totalSteps n =
    n*(totalSteps (n-1)) + (factorial (n-1))*(2^(n-1)-1) 

meanSteps n =
    (fromIntegral (totalSteps n))/(fromIntegral (factorial n))

main =
    print(meanSteps 30)