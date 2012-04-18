#include <stdlib.h>
#include "thc.h"

int *prime_factors(int n, int *result_size) {
    int *result;
    int prime = 2;
    result = malloc(sizeof(int) * 1024);
    *result_size = 0;
    while (n > 1) {
        if (n % prime == 0) {
            result[(*result_size)++] = prime;
            while (n % prime == 0) {
                n /= prime;
            }
        }
        prime++;
    }
    return result;
}

void test_number_with_no_prime_factors() {
    int size, *primes;
    primes = prime_factors(1, &size);
    ENSURE(size == 0);
    free(primes);
}

void test_number_with_only_one_prime_factor() {
    int size, *primes;
    primes = prime_factors(2, &size);
    ENSURE(size == 1);
    ENSURE(*primes == 2);
    free(primes);
}
void test_number_with_one_prime_factor_multiple_times() {
    int size, *primes;
    primes = prime_factors(4, &size);
    ENSURE(size == 1);
    ENSURE(*primes == 2);
    free(primes);
}

void test_number_with_two_prime_factors_multiple_times() {
    int size, *primes;
    primes = prime_factors(26, &size);
    /*
       26 | 2
       13 | 13
       1
    */
    ENSURE(size == 2);
    ENSURE(primes[0] == 2);
    ENSURE(primes[1] == 13);
    free(primes);
}

int main(void) {
    thc_addtest(test_number_with_no_prime_factors);
    thc_addtest(test_number_with_only_one_prime_factor);
    thc_addtest(test_number_with_one_prime_factor_multiple_times);
    thc_addtest(test_number_with_two_prime_factors_multiple_times);
    return thc_run(1);
}
