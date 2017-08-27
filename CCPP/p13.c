#include <stdio.h>
#include <gmp.h>

int main() {
    FILE *file;
    char buffer[128];
    mpz_t rez, cnm;

    mpz_init(rez); mpz_init(cnm);
    mpz_set_ui(rez, 0);

    file = fopen("p13.txt", "r");

    if (file == NULL) return 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        mpz_set_str(cnm, buffer, 0);
        mpz_add(rez, rez, cnm);
    }

    return gmp_printf("%Zd\n", rez);
}