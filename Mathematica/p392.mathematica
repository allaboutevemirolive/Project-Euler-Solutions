circ[x_] = Sqrt[1 - x^2];
n = 200;
xs = Symbol["x" <> ToString[#]] & /@ Range[1, n];
area := 4*(xs[[1]] + circ[xs[[-1]]]*(1 - xs[[-1]]) + 
    Sum[(xs[[i + 1]] - xs[[i]])*circ[xs[[i]]], {i, 1, n - 1}])
startings := {xs[[#]], Sin[(1/2) Pi (# + 1)/(n + 2)]} & /@ Range[1, n]
Timing@First@
  FindMinimum[area, startings, WorkingPrecision -> 13, 
   MaxIterations -> 10000]