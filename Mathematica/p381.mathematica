modinv[x_, p_] := ExtendedGCD[x, p][[2, 1]]
S[p_] :=  Mod[modinv[p - 2, p] + modinv[(p - 2) (p - 3), p] + modinv[(p - 2) (p - 3) (p - 4), p], p]
ParallelSum[S[p], {p, Prime /@ Range[3, PrimePi[10^8]]}]