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
    unsigned long int seed = 0;
    FILE *urandom;

    urandom = fopen("/dev/urandom", "r");

    if (urandom) {
        if (fread(&seed, sizeof(seed), 1, urandom)) {
                fclose(urandom);
        } else {
            die("/dev/urandom could not be read.");
        }
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

int main(int argc, char *argv[])
{
    int i;
    double rnd;
    double mu;

    if (argc != 5) die("Four arguments are required:\n./decay tau_1 tau_2 alpha number");

    double tau_1 = atof(argv[1]);
    double tau_2 = atof(argv[2]);
    double alpha = atof(argv[3]);
    int num_values = atoi(argv[4]);

    if (tau_1 < 0 || tau_2 < 0) die("Lifetime values should be positive.");
    if (alpha <= 0 || alpha >= 1) die("Alpha must be between 0 and 1.");
    if (num_values < 1) die("At least 1 value must be required.");

    gsl_rng * r = init_rng();

    for (i = 0; i < num_values; i++) {
        rnd = gsl_rng_uniform(r);
        if (rnd < alpha) {
            mu = tau_1;
        } else {
            mu = tau_2;
        }

        double t = gsl_ran_exponential(r, mu);
        printf("%f\n", t);
    }

    gsl_rng_free(r);
    return 0;
}
