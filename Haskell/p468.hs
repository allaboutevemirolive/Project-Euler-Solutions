data Affine i = Affine !i !i

(*:) :: Num i => Affine i -> Affine -> Affine i
(*:) (Affine a b) (Affine c d) = Affine (a * c) (a * d + b)

($:) :: Num i => Affine i -> i -> i
($:) (Affine a b) x = a * x + b

instance Num a => Monoid (Affine a) where
    mappend = flip (*:)
    mempty = Affine 1 0
f_st :: Int -> Int
f_st n = runST $ do
    tree <- newLMSegTree V {- (Affine 1 0) (flip (*:)) -} 0 n
            :: ST s (LMSegTreeV s SlimVector.MVector Int (Affine (Mod Int)))
    forM_ (upto n primes) $ \p ->
        let (q, r) = n `divMod` p in
        VU.forM_ (VU.enumFromN 0 (q + 1)) $ \k -> do
            let m1 = borrows p q k
                m2 = borrows p n (k * p + r + 1)
                g 0 _ _ = return ()
                g m l u = do unsafeIOToST $ putStrLn "()"
                            leftMonoidMulRange l u (mat p m) tree
                mat p' m = Affine pm ((1 - pm) * (p - 1))
                    where p = fI p'
                        pm = p^m
            g m1 (k * p) (k * p + r)
            g m2 (k * p + r + 1) (k * p + p - 1)
        v <- toMonoidVector tree
        let n' = fI n
        return $ unMod $ V.foldl' (\acc m -> acc + (m $: n')) 0 v
