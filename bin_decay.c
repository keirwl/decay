#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define INITIAL_LINE_LENGTH (8)

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
    if (argc != 3) die("Two arguments are required:\nbin_decay.app number_bins bin_width");

    const int number_bins = atoi(argv[1]);
    const double bin_width = atof(argv[2]);

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

    double data;
    int bin_index;
    char *line = NULL;
    size_t size = 0;
    ssize_t line_len;
    while ((line_len = getline(&line, &size, stdin)) != -1) {
        data = atof(line);
        bin_index = (int)(data/bin_width);
        if (bin_index >= number_bins) continue;

        n[bin_index] += 1;
    }
    free(line);

    for (i = 0; i < number_bins; i++) {
        printf("%g %i\n", t[i], n[i]);
    }

    return 0;
}
