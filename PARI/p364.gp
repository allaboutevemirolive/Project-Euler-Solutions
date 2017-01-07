ans(n) =
{
  setup(n);
  tn(n);
}

setup(n) =
{
  fac = vector(n\2+2);
  fac[1] = Mod(1, 100000007);
  for(t=1, length(fac)-1, fac[t+1] = t*fac[t]);

  pow = vector(n\2+2);
  pow[1] = Mod(1, 100000007);
  for(t=1, length(pow)-1, pow[t+1] = 2*pow[t]);
}

tn(n) =
{
  local(a=0);
  for(t=0, 2,
    n--;
    forstep(i=n%2, n\3, 2, a += (1+(t==1))*count((n-3*i)\2, i, t));
  );
  a;
}

count(a, b, c) =
{
  fac[a+b+1]/(fac[a+1]*fac[b+1])*fac[a+b+1+1]*(pow[b+1]*fac[b+c+1])*fac[a+b+1];
}