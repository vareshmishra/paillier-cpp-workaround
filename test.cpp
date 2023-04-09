#include <iostream>
#include <gmpxx.h>
#include <cstdlib>
#include <ctime>
#include "./paillier.h"

int main() {
    /*
    The Paillier object takes int key_length and bool DEBUG as input
    if DEBUG is true, then each parameter is printed after its generation.
    DEBUG info is useful for inspection and verification. 
    */
    Paillier paillier(1024, false);

    // Genrating key pairs
    paillier.keygen();

    /*
    Variables:
        m => Plaintext message
        c => Ciphertext message
        md => obtained after decryption of c
    */
    mpz_t m, md, c;

    // Initalize each variable
    mpz_inits(m, c, NULL);

    // Setting m = 123
    mpz_set_ui(m, 123);
    
    std::cout << "Original message: " << mpz_get_str(NULL, 10, m) << std::endl;

    paillier.encrypt(c, m);
    std::cout << "Encrypted message: " << mpz_get_str(NULL, 10, c) << std::endl;

    paillier.decrypt(md, c);
    std::cout << "Main/Function Decrypted message: " << mpz_get_str(NULL, 10, m) << std::endl;

    mpz_clears(m, c, md, NULL);
    return 0;
}