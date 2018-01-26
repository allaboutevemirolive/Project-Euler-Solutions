maxArea3 :: (Int, Int, Int) -> Double
maxArea3 (a', b', c') = maxArea3' (fromIntegral a') (fromIntegral b') (fromIntegral c') where
    maxArea3' :: Double -> Double -> Double -> Double
    maxArea3' a b c = pi * (r1_2 + r2_2 + rFinal_2) where
        p = (a + b + c) / 2
        sin2a = (a^2 - (b - c)^2) / (4 * b * c)
        cos2a = ((b + c)^2 - a^2) / (4 * b * c)
        sin2b = (b^2 - (c - a)^2) / (4 * c * a)
        cos2b = ((c + a)^2) / (4 * c * a)
        sina = sqrt sin2a
        cosa = sqrt cos2a
        radicand2_a = (1 - sina) / (1 + sina)
        radicand2_b = (1 - sinb) / (1 + sinb)
        sinb = sqrt sin2b
        cosb = sqrt cos2b
        r1_2 = (p - a) * (p - b) * (p - c) / p
        r2_2 = r1_2 * (1 - sina)^2 / cos2a * radicand2_a
        r3_2 = r1_2 * (1 - sinb)^2 / cos2b * radicand2_b
        r4_2 = r2_2 * (1 - 2 * sina / cosa * sqrt(radicand2_a))^2
        rFinal_2 = max r3_2 r4_2