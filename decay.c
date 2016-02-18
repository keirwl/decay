#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

unsigned long int random_seed()
{
    unsigned int seed = 0;
    FILE *urandom;

    urandom = fopen("/dev/urandom", "r");

    if (urandom) {
        fread(&seed, sizeof(seed), 1, urandom);
        fclose(urandom);
    } else {
        die("/dev/urandom could not be opened.");
    }

    return seed;
}

gsl_rng * init_rng()
{
    const gsl_rng_type * T = gsl_rng_default;
    const unsigned long int seed = random_seed();

    gsl_rng * r = gsl_rng_alloc(T);
    gsl_rng_set(r, seed);

    return r;
}

int main()
{
    gsl_rng * r = init_rng();

    double i = gsl_ran_exponential(r, 3.0);
    printf("Value: %f\n", i);

    gsl_rng_free(r);
    return 0;
}
