#include <iostream>
#include "math.h"
using namespace std;

#define N 1000000000000L
#define fourN 4*N

int main() {
    __int64 x, x2, l0, l, p, p2, f, px, px2, lpx, plpx, plpx2;
    __int64 sum = 0, sum1 = 0, suml = 0, sum10 = 0;
    __int64 triangx, triangx2;

    // case x = 0
    l = N % 2400000000L;
    p = (l * (l + 1)) % 2400000000L;
    p2 = (p*p) % 2400000000L;
    f = (10*p + p2)/24;
    f = f + l + 1;
    sum = (sum + 2*f) % 100000000;

    // case x = 2, this is the general term for x > 2 the minds can be removed
    x = 2;

    {
        l0 = (4*N-x*x)/(2*x);
        l = min<__int64>(l0,N-x);
        l = l % 2400000000L;
        p = (l*(l+1)) % 2400000000L;
        p2 = (p*p) % 2400000000L;
        f = (10*p + p2)/24 + l;
        l = min<__int64>(l0,N+x);
        l = l % 2400000000L;
        lpx = (l+x);
        plpx = (lpx*(lpx+1)) % 2400000000L;
        plpx2 = (plpx*plpx) % 2400000000L;
        px = ((x-1)*x) % 2400000000L;
        px2 = (px*px) % 2400000000L;
        f += (10*(plpx-px)+plpx2-px2)/24 + l;
        sum = sum + 2*f;
    }

    // main loop
    suml = 0;
    sum1 = 0;
    sum10 = 0;
    x = 4;

    while ((x2=x*x)<=fourN) {
        l      = ((fourN-x2)/(2*x))        % 1200000000L;
        suml  += l;
        p      = (l*(l+1))                 % 1200000000L;
        plpx   = ((l+x)*(l+x+1))           % 1200000000L;
        px     = (x2-x)                    % 1200000000L;
        sum1  += (p*p + plpx*plpx - px*px) % 1200000000L;
        sum10 +=  p   + plpx      - px;
        x     += 2;
    }

    sum = sum                        % 100000000;
    sum = (sum + 4*suml)             % 100000000;
    sum = (sum + (10*sum10+sum1)/12) % 100000000;
    sum--; // because point (0,0) gets counted twice
    sum += (2*x-4); // +1 removed from f

    // subtract f(x) for x = 2, ... x*x<=4*N
    x = (x-2)/2;
    triangx  = (x*(x+1))         % 1200000000L;
    triangx2 = (triangx*triangx) % 1200000000L;
    sum = sum - ( x + (16*triangx2 + 10*triangx)/12 );

    sum = sum % 100000000;
    if (sum < 0) sum += 100000000;
    cout << "sum = " << sum << "\n";

    return 0;
}
