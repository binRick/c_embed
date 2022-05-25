
#include "options.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check whether the next argument matches a pattern
static bool arg_match(const char *arg, const char *sopt, const char *lopt)
{
    return strcmp(arg, sopt) == 0 || strcmp(arg, lopt) == 0;
}

// Get the next argument and convert it to float
static float get_float(int argc, char **argv, int *i)
{
    if (++(*i) == argc) {
        fprintf(stderr, "coloricious: %s: Expected argument", argv[(*i) - 1]);
        exit(EXIT_FAILURE);
    }

    const char *arg = argv[*i];
    float value = atof(arg);

    return value;
}

void parse_options(struct options *opts, int argc, char **argv)
{
    // Set defaults
    opts->period = 35.0;
    opts->saturation = 0.65;
    opts->value = 0.9;
    opts->escaped = false;

    for (int i = 1; i < argc; ++i) {

        const char *arg = argv[i];

        if (arg_match(arg, "-h", "--help")) {

            fprintf(stdout, "coloricious - Colorize your terminal output\n"
                "\n"
                "Usage: coloricious [ <options> ]\n"
                "\n"
                "Available options:\n"
                "  -h, --help        Show this help text\n"
                "  -p, --period      Set the color band period\n"
                "  -s, --saturation  Set the output saturation\n"
                "  -v, --value       Set the output brightness\n"
                "  -e, --escape      Write literal \\ characters\n"
            );

            exit(EXIT_SUCCESS);

        } else if (arg_match(arg, "-p", "--period")) {
            opts->period = get_float(argc, argv, &i);
        } else if (arg_match(arg, "-s", "--saturation")) {
            opts->saturation = get_float(argc, argv, &i);
        } else if (arg_match(arg, "-v", "--value")) {
            opts->value = get_float(argc, argv, &i);
        } else if (arg_match(arg, "-e", "--escaped")) {
            opts->escaped = true;
        } else {
            fprintf(stderr, "coloricious: %s: Unknown argument\n", arg);
            exit(EXIT_FAILURE);
        }

    }
}

