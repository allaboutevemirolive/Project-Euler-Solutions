#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <iostream>

typedef unsigned long long llu;

template<llu m>
struct modular {
    modular() : val() {}
    modular(llu a) : val(a % m) {}

    inline modular<m> operator+(modular<m> const& rhs) {
        return modular<m>(val + rhs.val);
    }
    
}