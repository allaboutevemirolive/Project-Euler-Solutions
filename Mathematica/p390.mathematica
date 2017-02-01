limit = 10^10;
tl = Sqrt[limit];
hits = ConstantArray[{0, 0}, tl + 1];
sum = 0;
fnd = {};
nxt[x_, y_, b_] := {x*(2 b^2 + 1) + (b^2 + 1)*y*2 b, 
   x*2 b + y*(2 b^2 + 1)};
Do[
  {
   t = 2 b^2 + 1; u = 2 b;
   set = Union[hits[[b]]];
   Do[
    {
     ys = set[[i]];
     Do[
      {
       y = ys;
       x = Sqrt[(b^2 + 1) y^2 + b^2];
       While[x <= 2 limit,
        {
         If[
          EvenQ[x] && y > b && Not[MemberQ[fnd, {b, y}]], {sum += x/2;
            AppendTo[fnd, {b, y}]}];
         If [b < y <= tl, AppendTo[hits[[y]], b]];
         new = nxt[x, y, b];
         x = new[[1]]; y = new[[2]];
         }];
       ys = -ys
       }, {2}]
     }, {i, 1, Length[set]}];
   AppendTo[hits[[b + 1]], b];
   }, {b, 1, tl}];
sum