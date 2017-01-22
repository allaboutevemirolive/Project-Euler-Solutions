In[1]:= IsTriplet[a_, b_, c_] := a^2 + b^2 == c^2

In[2]:= (
 n = 1000;
 c = b = 0;
 For[c = 1, c <= Ceiling[n - c / 2], c++,
  For[b = c, b >= Round[n - c / 2] - c, b--,
   If[n - b - c > 0 && isTriplet[n - b - c, b, c],
    Print[{n - b - c, b, c, (n - b - c) * b * c}]
    ]
   ]
  ]
 )