import qualified Data.Map as M
import System.Environment
import Control.Parallel.Strategies

-- assume m is small
solve :: Integer -> Integer -> Integer
solve n m = sum (parMap rseq bar [1..m])
    where foo i = foldl next (M.singleton i 1) [i+1..m]
          next m j = M.unionWith (+) m . fmap negate . M.mapKeysWith (+) (lcm j) $ m
          bar i = M.foldWithKey (\k a b -> b + a * (n*i `div` k)) 0 (foo i)

main = do
    print $ solve 64 10000000000000000