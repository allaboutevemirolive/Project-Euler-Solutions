Parallelize@
 Sum[r = n/2^IntegerExponent[n, 2]/5^IntegerExponent[n, 5];
  MultiplicativeOrder[10, r], {n, 100000000}] - Position[Divisors[2^26*5^11],100000000][[1,1]]
