polc(n,p) = {
  local(m,pp,v);
  m = 1;
  pp = 0;
  while(m<=n,
    pp = pp+1;
    m *= p
  );
  m = m/p;
  v = vector(pp);
  pp = pp-1;
  while(pp > 0,
    v[pp+1] = n\m;
    n = n - v[pp+1]*m;
    m = m/p;
    pp = pp-1;
  );
  v[1] = n;
  return(v);
}

bmod(nv,mv,p) = {
  local(v);
  v = Mod(1,p);
  for(i=1,#mv,
    v = v * binomial(nv[i],mv[i]);
  );
  return(v);
}

main() = {
  pr=primes(669);
  pncoeffs = vector(#pr,i,polc(10^18,pr[i]));
  pmcoeffs = vector(#pr,i,polc(10^9,pr[i]));
  bmodp = vector(#pr,i,bmod(pncoeffs[i],pmcoeffs[i],pr[i]));
  ss = 0;
  for(pi=169,#pr,
    for(qi=pi+1,#pr,
      cpq = chinese(bmodp[pi],bmodp[qi]);
      for(ri=qi+1,#pr,
        cpqr = chinese(cpq,bmodp[ri]);
        ss += lift(cpqr);
      )));
  print(ss);
}

main();
quit();