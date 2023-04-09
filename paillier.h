#include <gmpxx.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Paillier {
private:
    mpz_t n, n_squared, g, lambda, mu;
    int key_size = 1024;
    bool DEBUG = false;

public:
    Paillier(int key_length, bool debug);

    void keygen();

    void encrypt(mpz_t c, mpz_t m);

    void decrypt(mpz_t m_input, mpz_t c);

    ~Paillier();
};