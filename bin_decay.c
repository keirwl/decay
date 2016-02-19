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

char * get_line(void)
{
    char * line;
    int size; // how much space in line
    int length; // how many characters in line
    int c;

    size = INITIAL_LINE_LENGTH;
    line = malloc(size);
    if (!line) die("Memory error.");
    length = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (length >= size-1) {
            size *= 2;
            line = realloc(line, size);
        }

        line[length++] = c;
    }

    line[length] = '\0';
    return line;
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

    char *line;
    double data;
    int bin_index;
    i = 0;
    while ((line = get_line()) && i < number_values) {
        // printf("Read %i lines\n", i);
        data = atof(line);
        free(line); // every iteration of loop calls a malloc, thus must be freed here

        bin_index = (int)(data/bin_width);
        if (bin_index >= number_bins) continue;

        n[bin_index] += 1;
        i++;
    }

    free(line); // upon final get_line(), loop is never ran, thus must be freed here too

    for (i = 0; i < number_bins; i++) {
        printf("%g %i\n", t[i], n[i]);
    }

    return 0;
}
