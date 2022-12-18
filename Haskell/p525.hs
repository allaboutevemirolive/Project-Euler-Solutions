import Numeric.Tools.Integration
import Data.Maybe(fromJust)
import Text.Printf

path::Double -> Double -> Double
path a b = fromJust $ quadRes $ quadRomberg defQuad (0, 2*pi) ds
    where
        ds t    = min a b * sqrt(1 - e2*cos t^2) / (1 - e2*sin t^2)
        e2      = 1 - (min a b/max a b)^2

main = printf "%.8f\n" $ path 1 4 + path 3 4