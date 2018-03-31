import Data.Ratio ( (%) )
import Text.Printf ( printf )
import Math.Combinat.Numbers ( binomial )

main = printf "%.9f\n" ((*7) $ (1-) $ fromRational $ binomial 60 20 % binomial 70 20 :: Double)