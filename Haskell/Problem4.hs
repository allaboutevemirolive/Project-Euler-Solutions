-- Determines if a number is a palindrome
	isPalindrome :: Int -> Bool
	isPalindrome n = n == (read (reverse (show n)) :: Int)

	Problem4 :: Int
	Problem4 = maximum [a * b | a <- [100..999], b <- [a..999], isPalindrome (a * b)]

	main :: IO()
	main = print Problem4