import Char
import List

names = sort ["names.txt"]
main = print . sum . zipWith (*) [1..] .
    map (sum . map ((subtract 64) . ord)) $ names