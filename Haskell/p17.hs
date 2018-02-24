module Main where 
import Data.Char

smallNums = ["", "one", "two", "three", "four", "five",
            "six", "seven", "eight", "nine", "ten",
            "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"]
tensNums = ["", "", "twenty", "thirty", "forty", "fifty", 
            "sixty", "seventy", "eighty", "ninety"]

digits = (map digitToInt) . show

wordify n = case digits n of
    [ones] -> smallNums !! n
    [1, ones] -> smallNums !! n
    [tens, 0] -> tensNums !! tens
    [tens, ones] -> (tensNums !! tens) ++ "-" ++ (smallNums !! ones)
    [hundreds, 0, 0] -> (smallNums !! hundreds) ++ " hundred"
    [hundreds, tens, ones] -> (smallNums !! hundreds) ++ " hundred and " ++ (wordify (tens * 10 + ones))
    [1, 0, 0, 0] -> "one thousand"

main = print . length . filter (\x -> x >= 'a' && x <= 'z') . concat . map wordify $ [1..1000]
