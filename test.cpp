#include <iostream>
#include <gmpxx.h>
#include <cstdlib>
#include <ctime>
#include "./paillier.h"

int main() {
    Paillier paillier(1024, false);
    paillier.keygen();
    mpz_t m, m2, c;
    mpz_inits(m, c, NULL);
    mpz_set_ui(m, 142);
    mpz_set_ui(m2, 1);
    std::cout << "Original message: " << mpz_get_str(NULL, 10, m) << std::endl;

    paillier.encrypt(c, m);
    std::cout << "Encrypted message: " << mpz_get_str(NULL, 10, c) << std::endl;

    paillier.decrypt(m2, c);
    std::cout << "Main/Function Decrypted message: " << mpz_get_str(NULL, 10, m) << std::endl;

    mpz_clears(m, c, m2, NULL);
    return 0;
}