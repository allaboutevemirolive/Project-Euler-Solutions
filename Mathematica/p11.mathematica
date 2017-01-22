In[1]:= triangleNumber[n_Integer] := Fold[Plus, Range[n]]

In[2]:= (
 i = 1; t = 0;
 While[Length[Divisors[t = triangleNumber[i]]] <= 500, i++];
 t
  Clear[t, i];
 )