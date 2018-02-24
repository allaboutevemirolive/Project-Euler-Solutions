import Data.Time.Calendar
import Data.Time.Calendar.WeekDate

main = print $ length $ filter (\(a, b, c) -> (c == 7)) [toWeekDate $ fromGregorian a b 1 | a <- [1901..2000], b <- [1..12]]
