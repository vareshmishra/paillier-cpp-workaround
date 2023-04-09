#include <iostream>
#include <gmpxx.h>
#include <cstdlib>
#include <ctime>
#include "./paillier.h"
/*
From https://en.wikipedia.org/wiki/Paillier_cryptosystem
If using p,q of equivalent length a simpler variant of the above key generation steps would be to:
g = n + 1
lambda = phi(n)
mu = {phi(n)}^-1 mod n
*/


Paillier::Paillier(int key_length, bool debug) {
    mpz_inits(n, n_squared, g, lambda, mu, NULL);
    key_size = key_length;
    DEBUG = debug;
}

void Paillier::keygen() {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // Set random seed
    srand(time(NULL));
    unsigned long seed = rand();
    gmp_randseed_ui(state, seed);

    // Generate two large primes
    mpz_t p, q, phi_n;
    mpz_inits(p, q, phi_n, NULL);

    mpz_urandomb(p, state, key_size/2);   // Generate a uniformly distributed random integer in the range 0 to 2^(ks/2)-1, inclusive.
    mpz_urandomb(q, state, key_size/2);  // Generate a uniformly distributed random integer in the range 0 to 2^(ks/2)-1, inclusive.
    
    mpz_nextprime(p, p);   // Compute the next prime greater than p and store it in p
    mpz_nextprime(q, q);   // Compute the next prime greater than q and store it in q
    if (DEBUG) {
        std::cout << "Generating p: " << mpz_get_str(NULL, 10, p) << std::endl << std::endl;
        std::cout << "Generating q: " << mpz_get_str(NULL, 10, q) << std::endl << std::endl;
    }
    
    // Calculate n, n_squared, and lambda
    mpz_mul(n, p, q);
    mpz_mul(n_squared, n, n);
    if (DEBUG) {
        std::cout << "Generating n: " << mpz_get_str(NULL, 10, n) << std::endl << std::endl;
        std::cout << "Generating n_squared: " << mpz_get_str(NULL, 10, n_squared) << std::endl << std::endl;
    }

    // Calculate p-1, q-1, phi_n and lambda
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi_n, p, q);
    mpz_set(lambda, phi_n);
    if (DEBUG) {
        std::cout << "Generating p-1: " << mpz_get_str(NULL, 10, p) << std::endl << std::endl;
        std::cout << "Generating q-1: " << mpz_get_str(NULL, 10, q) << std::endl << std::endl;
        std::cout << "Generating phi_n: " << mpz_get_str(NULL, 10, phi_n) << std::endl << std::endl;
        std::cout << "Generating lambda: " << mpz_get_str(NULL, 10, lambda) << std::endl << std::endl;
    }

    // Choose g
    mpz_add_ui(g, n, 1);
    
    // Calculate mu
    mpz_invert(mu, phi_n, n);
    if (DEBUG) {
        std::cout << "Generating g: " << mpz_get_str(NULL, 10, g) << std::endl << std::endl;
        std::cout << "Generating mu: " << mpz_get_str(NULL, 10, mu) << std::endl << std::endl;
    }
    
    // Clear
    mpz_clears(p, q, phi_n, NULL);
}

void Paillier::encrypt(mpz_t c, mpz_t m) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // Set random seed
    srand(time(NULL));
    unsigned long seed = rand();
    gmp_randseed_ui(state, seed);

    mpz_t r, g_m, g_r, r_n;
    mpz_inits(r, g_m, g_r, r_n, NULL);
    mpz_urandomm(r, state, n);

    if (DEBUG)
        std::cout << "Random r: " << mpz_get_str(NULL, 10, r) << std::endl << std::endl;

    mpz_powm(g_m, g, m, n_squared);
    mpz_powm(r_n, r, n, n_squared);
    mpz_mul(c, g_m, r_n);
    mpz_mod(c, c, n_squared);

    // Clear r
    mpz_clears(r, g_m, g_r, r_n, NULL);
}

void Paillier::decrypt(mpz_t m_input, mpz_t c) {
    mpz_t L, c_lambda;
    mpz_inits(L, c_lambda, NULL);
    
    mpz_set_ui(L, 2);
    mpz_powm(c_lambda, c, lambda, n_squared);
    mpz_sub_ui(c_lambda, c_lambda, 1);
    mpz_tdiv_q(L, c_lambda, n);
    mpz_mul(m_input, L, mu);
    mpz_mod(m_input, m_input, n);
    mpz_clears(L, c_lambda, NULL);
}

Paillier::~Paillier() {
    mpz_clears(n, n_squared, g, lambda, mu, NULL);
}


