#include <iostream>
using namespace std;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#define L 100000000ULL

u64 gcd(u64 a,u64 b){
	while(b){
		u64 c=a%b; a=b; b=c;
	}
	return a;
}

u64 powmod(u64 x,u64 y,u64 m){
	u64 r=1;
	for( ; y; y >>= 1) {
		if(y & 1) r = r * x % m;
		x = x * x % m;
	} return r;
}

u32 np[L+1];
u32 lcm[L+1];

int main() {
  for(u64 n=0;n<=L;n++) lcm[n]=1;
  for(u64 x=1;x<=L;x*=2)
  for(u64 y=x;y<=L;y*=5)
    lcm[y]=0;

  for(u64 n=2;n<=L;n++) if(!np[n]) {
    for(u64 x=n;x<=L;x+=n)  np[x]=n;

    if(n==5)continue;
    if(n==2)continue;

    u64 d=n-1;
    u64 x=n-1;
    while(x>1) {
      u64 f=np[x]; do x/=f; while(x%f==0);
      while(d%f==0 && powmod(10,d/f,n)==1) d/=f;
    }

    u64 nn=n,n1=n;
    if(n==3)nn*=3;
    if(n==487)n1=1;

    for(u64 y=d; nn<=L; nn*=n,y*=n1)
    for(u64 x=nn; x<=L; x+=nn)
       lcm[x] = lcm[x]/gcd(lcm[x],y)*y;
  }

  u64 s=0;
  for(u64 x=2;x<=L;x++) s+=lcm[x];
  cout << s << endl;

  return 0;
}
