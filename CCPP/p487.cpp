#include <cstdio>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

static const ull PRIME1 = 0x3f91300000000001ULL;
static const ull PRIME2 = 0x3f93300000000001ULL;
static const ull PRIME1_INV_MOD_PRIME2 = 0x19D3CB8000001FCAULL;

static const ull PERI2 = 44;
static const ull ROOTS1[] = {
    1819933121506474219llu, 1989036478871360832llu, 4222294568819848826llu, 524016996894354223llu,
    2660749113542353830llu, 290449864440316070llu, 4242685559443468351llu, 478971818174369032llu,
    4408964714607736735llu, 2454232280409617688llu, 1496365293496365995llu, 2009203248790022989llu,
    1141575224888668082llu, 337999907025289251llu, 4363613503691128143llu, 289262737020117728llu,
    4517591918414607824llu, 3605908247597146966llu, 1628237650652718133llu, 1048979789291022161llu,
    2941395220051623499llu, 777439875064665625llu, 1997487648144915967llu, 891772685373118735llu,
    3137848140478108969llu, 2950092101171464837llu, 1857847415763309056llu, 2633314194512013828llu,
    149623711620902439llu, 1860593840098573130llu, 1675329833173581125llu, 2446135922790467931llu,
    887046318435095557llu, 938264187555842302llu, 4478160933281968419llu, 3825473630150211720llu,
    3600552148240914448llu, 986109833013357164llu, 1260051638314148464llu, 619412925070657041llu,
    2254532335337795749llu, 3654714190152744984llu, 3731105725231685020llu, 4580495072570638336llu, 
    1llu
};
static const ull ROOTS2[] = {
    4128580147792844837llu, 3929429105631915857llu, 4477602444661007704llu, 2652177470024758533llu,
    773382505417085040llu, 1143373611369722503llu, 1566599294584451005llu, 1686690010620531680llu,
    888478481167098404llu, 2756853601593197762llu, 894154222853272184llu, 3849847911299636702llu,
    1063305160208088819llu, 2943843754677269575llu, 510995518905818165llu, 3589199057278418673llu,
    1768418756009568938llu, 4171507976151104419llu, 3409261184903313814llu, 2877261320902492722llu,
    2154839116516463711llu, 374219467974515067llu, 373584053649738564llu, 4538814142955366967llu,
    1280801167944422637llu, 1232214045327986759llu, 309265297569377902llu, 4498001700753361615llu,
    2463974555221756338llu, 2169896482352819703llu, 2427171750120132590llu, 1637927932066548008llu,
    4442710565864836214llu, 4359435400269042297llu, 2146234623747541478llu, 4312351551771097465llu,
    292149728943690925llu, 165172724634487328llu, 4362931320767009048llu, 2380519221369126555llu,
    1107766252674133626llu, 314721577461726505llu, 3812943061848153207llu, 4581058022524059648llu,
    1llu
};

template <ull mod>
class Mod {
public:
    Mod() {  }
    Mod(ull v) : n(v) {  }

    Mod operator+ (Mod rhs) const {
        ull ret = (this->n + rhs.n);
        return Mod(ret >= mod ? ret - mod : ret);
    }

    Mod operator- (Mod rhs) const {
        ull ret = (this->n - rhs.n);
        return Mod(ll(ret) < 0 ? ret + mod : ret);
    }

    Mod operator* (Mod rhs) const {
        return Mod(mul_mod(this->n, rhs.n));
    }

    Mod operator+= (Mod rhs) {
        return *this = *this + rhs;
    }

    Mod operator-= (Mod rhs) {
        return *this = *this + rhs;
    }

    Mod operator*= (Mod rhs) {
        return *this = *this * rhs;
    }

    ull get_value() const {
        return this->n;
    }

    void set_value(ull val) {
        this->n = val;
    }

    Mod inverse() {
        return Mod(pow_mod(n, mod - 2));
    }

    static ull mul_mod(ull a, ull b) {
        ull q = ull(ld(a) * ld(b) * (ld(1) / mod) + ld(1) / 2);
        ull r = a * b - mod * q;
        if (ll(r) < 0) {
            r += mod;
        }
        return r;
    }

    static ull pow_mod(ull base, ull exp) {
        ull ret = 1;
        ull q = base;
        while (exp) {
            if (exp & 1) {
                ret = mul_mod(ret, q);
            }
            q = mul_mod(q, q);
            exp >>= 1;
        }
        return ret;
    }
private:
    ull n;
};

typedef Mod<PRIME1> mod_t1;
typedef Mod<PRIME2> mod_t2;

template <typename T>
inline void sumdiff(T& a, T& b) {
    T t = a - b;
    a += b;
    b = t;
}

template <typename T>
void revbin_permute(T* A, uint n) {
    if (n <= 2) return;
    uint r = 0;
    uint nh = n >> 1;
    for (uint x = 1; x < n; ++x) {
        uint h = nh;
        while(!((r ^= h) & h))
            h >>= 1;
        if (r > x)
            swap(A[x], A[r]);
    }
}

template <typename T>
void ntt_dit2_core(T *f, uint ldn, int sign, const ull* roots) {
    const uint n = 1u << ldn;
    for (uint i = 0; i < n; i += 2) {
        sumdiff(f[i], f[i + 1]);
    }

    for (uint ldm = 2; ldm <= ldn; ++ldm) {
        const uint m = 1u << ldm;
        const uint mh = m >> 1;

        T dw = T(roots[PERI2 - ldm]);
        if (sign < 0)
            dw = dw.inverse();

        T w = T(1);
        for (uint j = 0; j < mh; ++j) {
            for (uint r = 0; r < n; r += m) {
                const uint t1 = r + j;
                const uint t2 = t1 + mh;

                T v = f[t2] * w;
                T u = f[t1];

                f[t1] = u + v;
                f[t2] = u - v;
            }
            w *= dw;
        }
    }
}

template <typename T>
void ntt_dit2(T* f, uint ldn, int sign, const ull* roots) {
    revbin_permute(f, 1u << ldn);
    ntt_dit2_core(f, ldn, sign, roots);
}

uint pow_mod(uint base, uint exp, uint mod) {
    uint ret = 1;
    while (exp) {
        if (exp & 1) {
            ret = ull(ret) * base % mod;
        }
        base = ull(base) * base % mod;
        exp >>= 1;
    }
    return ret;
}

static const uint K_MAX = 10000;

mod_t1 A1[1u << 15];
mod_t2 A2[1u << 15];
mod_t1 B1[1u << 15];
mod_t2 B2[1u << 15];

uint a[K_MAX + 1];
uint b[K_MAX + 1];
uint stir2[K_MAX + 10];
uint invs[K_MAX + 10];

void convolve(uint size, uint mod) {
    uint ldn = 1;
    while ((1u << ldn) < size) ++ldn;
    ++ldn;
    uint ntt_size = 1u << ldn;

    for (uint i = 0; i < size; ++i) {
        A1[i].set_value(a[i]);
        B1[i].set_value(b[i]);
    }
    memset(A1 + size, 0, sizeof(A1[0]) * (ntt_size - size));
    memset(B1 + size, 0, sizeof(B1[0]) * (ntt_size - size));
    memcpy(A2, A1, sizeof(A1[0]) * ntt_size);
    memcpy(B2, B1, sizeof(B1[0]) * ntt_size);

    ntt_dit2(A1, ldn, 1, ROOTS1);
    ntt_dit2(A2, ldn, 1, ROOTS2);
    ntt_dit2(B1, ldn, 1, ROOTS1);
    ntt_dit2(B2, ldn, 1, ROOTS1);
    ntt_dit2(B2, ldn, 1, ROOTS2);
    
    for (uint i = 0; i < ntt_size; ++i) {
        A1[i] *= B1[i];
        A2[i] *= B2[i];
    }
    ntt_dit2(A1, ldn, -1, ROOTS1);
    ntt_dit2(A2, ldn, -1, ROOTS2);

    mod_t1 d1 = mod_t1(ntt_size).inverse();
    mod_t2 d2 = mod_t2(ntt_size).inverse();

    for (uint i = 0; i < size; ++i) {
        ull x1 = (A1[i] * d1).get_value();
        ull x2 = (A2[i] * d2).get_value();
        if (x1 != x2) {
            ull dx = x2 - x1;
            if (ll(dx) < 0) {
                dx += PRIME2;
            }
            dx = mod_t2::mul_mod(dx, PRIME1_INV_MOD_PRIME2);
            x1 = (x1 + dx % mod * (PRIME1 % mod));
        }
        stir2[i] = x1 % mod;
    }
}

uint calc(uint N, uint K, uint P) {
    uint tab[2] = { 1, P - 1 };
    for (uint i = 0; i <= K; ++i) {
        a[i] = pow_mod(i, K, P);
        b[i] = tab[i & 1];
    }

    uint ifact = 1;
    invs[1] = 1;
    for (uint i = 2; i <= K + 2; ++i) {
        uint inv = invs[i] = ull(invs[P % i]) * (P - P / i) % P;
        if (i > K) continue;
        
        ifact = ull(ifact) * inv % P;
        a[i] = ull(a[i]) * ifact % P;
        b[i] = ull(b[i]) * ifact % P;
    }
    convolve(K + 1, P);

    ull ret = 0;

    uint prod = ull(N + 2) * (N + 1) % P * invs[2] % P;

    for (uint i = 1; i <= K; ++i) {
        prod = ull(prod) * (N + 1 - i) % P * invs[i + 2] % P * i % P;
        ret += ull(prod) * stir2[i] % P;
    }
    return ret % P;
}

const uint primes[] = {
    2000000011, 2000000033, 2000000063, 2000000087, 2000000089, 2000000099, 2000000137, 2000000141, 
    2000000143, 2000000153, 2000000203, 2000000227, 2000000239, 2000000243, 2000000269, 2000000273, 
    2000000279, 2000000293, 2000000323, 2000000333, 2000000357, 2000000381, 2000000393, 2000000407, 
    2000000413, 2000000441, 2000000503, 2000000507, 2000000531, 2000000533, 2000000579, 2000000603, 
    2000000609, 2000000621, 2000000641, 2000000659, 2000000671, 2000000693, 2000000707, 2000000731, 
    2000000741, 2000000767, 2000000771, 2000000773, 2000000789, 2000000797, 2000000809, 2000000833, 
    2000000837, 2000000843, 2000000957, 2000000983, 2000001001, 2000001013, 2000001043, 2000001049, 
    2000001089, 2000001097, 2000001103, 2000001109, 2000001119, 2000001127, 2000001137, 2000001149, 
    2000001151, 2000001167, 2000001173, 2000001187, 2000001229, 2000001233, 2000001247, 2000001257, 
    2000001277, 2000001287, 2000001349, 2000001359, 2000001379, 2000001413, 2000001457, 2000001511, 
    2000001517, 2000001527, 2000001539, 2000001551, 2000001557, 2000001583, 2000001599, 2000001623, 
    2000001629, 2000001649, 2000001677, 2000001727, 2000001743, 2000001821, 2000001833, 2000001851, 
    2000001881, 2000001929, 2000001953, 2000001973
};

void solve() {
    ull ans = 0;
    for (uint pi = 0; pi < 100; ++pi) {
        uint p = primes[pi];
        ans += calc(ull(1e12) % p, 10000, p);
    }
    printf("%llu\n", ans);
}

int main() {
    solve();
    return 0;
}
