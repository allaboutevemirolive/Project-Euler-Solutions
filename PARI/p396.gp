{
ks=[2,3,5,7,23,63,383,2047];s=2517;m=10^9;
for(i=1,#ks, k=ks[i];
  t=Mod(k,m)+1;
  for(j=0,k, t*=Mod(2,m)^(lift(t)+m*(j>0)));
  s+=t-3
);
lift(s)
}
