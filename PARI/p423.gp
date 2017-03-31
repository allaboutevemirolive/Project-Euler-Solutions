S=Mod(1+6+36, 10^9+7); Sc=Mod(36, 10^9+7);
Bk=Mod(1, 10^9+7);
n = 2;
for(k=4, 50000000,v=isprime(k);n+=v;Sc=if(v==0,6*Sc-Bk,6*Sc+Bk*(k-1-n)/(n));Bk *= if(v==0,5*(k-1)/(k-1-n),(k-1)/(n));S+=Sc);lift(6*S);
