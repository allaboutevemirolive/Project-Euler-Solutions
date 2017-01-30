S[n_] := (-4 n + 3 n^2 + n^3);
NN = 10^10;
sum = 7;
Do[
  If[SquareFreeQ[n],
   {
    ad = S[IntegerPart[NN/n]];
    If[EvenQ[PrimeNu[n]], sum += ad, sum -= ad]
    }]
  , {n, 1, NN/2}];
sum