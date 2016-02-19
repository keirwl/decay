#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 4) die("Three arguments are required:\nbin_decay.app number_bins bin_width number_values");

    const int number_bins = atoi(argv[1]);
    const double bin_width = atof(argv[2]);
    const int number_values = atoi(argv[3]);

    if (number_bins < 1 || bin_width <= 0) die("Bin number and width must be positive values.");

    int i = 0;
    double t[number_bins];
    for (i = 0; i < number_bins; i++) {
        t[i] = (i+1)*bin_width;
    }

    int n[number_bins];
    // n is the histogram counter, thus must be initialised to zeroes
    // this must be done by looping as it is dynamically allocated
    for (i = 0; i < number_bins; i++) {
        n[i] = 0;
    }

    char line[16];
    double data;
    int bin_index;
    i = 0;
    while (fgets(line, sizeof(line), stdin) && i < number_values) {
        // printf("Read %i lines\n", i);
        data = atof(line);
        bin_index = (int)(data/bin_width);
        if (bin_index >= number_bins) continue;

        n[bin_index] += 1;
        i++;
    }

    for (i = 0; i < number_bins; i++) {
        printf("%g %i\n", t[i], n[i]);
    }

    return 0;
}
