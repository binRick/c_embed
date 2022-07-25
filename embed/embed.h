#pragma once
#include "ansi-codes/ansi-codes.h"
#include "cargs/include/cargs.h"
#include "embed-utils/embed-utils.h"
#include "greatest/greatest.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
int parse_args(int, char **);
int debug_args();

#define DEFAULT_INPUT_FILE    "Makefile"
#define DEFAULT_OUTPUT_DIR    "embeds"
#define DEFAULT_VERBOSE       false
#define DEFAULT_MODE          "embed"
////////////////////////////////////////////////////////////////////

typedef struct CLI_ARGS {
  char *input_file;
  char *output_dir;
  char *mode;
  bool verbose;
} args_t;

static struct cag_option options[] = {
  { .identifier     = 'i',
    .access_letters = "i",
    .access_name    = "input-file",
    .value_name     = "INPUT",
    .description    = "Input File Path" },
  { .identifier     = 'o',
    .access_letters = "o",
    .access_name    = "output-dir",
    .value_name     = "OUTPUT_DIR",
    .description    = "Output Directory" },
  { .identifier     = 'm',
    .access_letters = "m",
    .access_name    = "mode",
    .value_name     = "MODE",
    .description    = "Mode" },
  { .identifier     = 'v',
    .access_letters = "v",
    .access_name    = "verbose",
    .value_name     = NULL,
    .description    = "Verbose Mode" },
  { .identifier     = 'h',
    .access_letters = "h",
    .access_name    = "help",
    .description    = "Shows the command help" }
};
