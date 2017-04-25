import Text.Printf (printf)
import Numeric.GSL.Integration (integrateQAGS)

main :: IO ()
main = printf "%.2f\n" (result::Double)
    where
        (n, m) = (10^10, 4000)
        f k = 0.5 * (1 - 2 * (1 - ((n - k)^2 + (k - 1)^2) / (n^2)))^m
        result = n / 2 + f 1 + (fst $ integrateQAGS 1e-10 100 f 1 n)

