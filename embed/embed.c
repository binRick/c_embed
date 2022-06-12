#include "embed.h"


args_t args = {
  DEFAULT_INPUT_FILE,
  DEFAULT_OUTPUT_DIR,
  DEFAULT_MODE,
  DEFAULT_VERBOSE,
};


int debug_args(){
  fprintf(stderr,
          ansistr(AC_BRIGHT_BLUE_BLACK AC_BOLD  "Verbose: %d")
          ", "
          ansistr(AC_RESETALL AC_BRIGHT_RED_BLACK "Input: %s")
          ", "
          ansistr(AC_RESETALL AC_BRIGHT_GREEN_BLACK "Output Directory: %s")
          ", "
          ansistr(AC_RESETALL AC_BRIGHT_GREEN_BLACK "Mode: %s")
          ", "
          "\n",
          args.verbose, args.input_file, args.output_dir, args.mode
          );

  return(EXIT_SUCCESS);
}


int main(int argc, char **argv) {
  (void)argc; (void)argv;
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf(AC_RESETALL AC_GREEN "OK\n" AC_RESETALL);
    return(EXIT_SUCCESS);
  }
  return(embed_main(argc, argv));

  parse_args(argc, argv);
  if ((strcmp(args.mode, "args") == 0)) {
    return(debug_args());
  }
}


int parse_args(int argc, char **argv){
  char               identifier;
  const char         *value;
  cag_option_context context;

  cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
  while (cag_option_fetch(&context)) {
    identifier = cag_option_get(&context);
    switch (identifier) {
    case 'm':
      value     = cag_option_get_value(&context);
      args.mode = value;
      break;
    case 'i':
      value           = cag_option_get_value(&context);
      args.input_file = value;
      break;
    case 'o':
      value           = cag_option_get_value(&context);
      args.output_dir = value;
      break;
    case 'v':
      args.verbose = true;
      break;
      break;
    case 'h':
      fprintf(stderr, AC_RESETALL AC_YELLOW AC_BOLD "Usage: parser [OPTION]\n" AC_RESETALL);
      cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
      exit(EXIT_SUCCESS);
    }
  }
  return(EXIT_SUCCESS);
} /* parse_args */
