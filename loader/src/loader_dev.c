/////////////////////////////////////////////
#include "../include/loader_dev.h"
#include "../include/loader_iterate.h"
#define BINARY_NAME    "loader_dev"


/////////////////////////////////////////////


static int print_help() {
  printf(
    "Usage:\n"
    "\t %s <command>\n\n"
    "Commands:\n"
    "\t names:   iterate file names\n"
    "\t sizes:   iterate file sizes\n"
    "\t dev1:    xxxxxxxxxxxxxxxxxx\n",
    BINARY_NAME
    );
  return(1);
}


static int cmd_sizes() {
  ITERATE_HASH(DEBUG_TBL_ITEM_SIZE);
  return(0);
}


static int cmd_names() {
  ITERATE_HASH(DEBUG_TBL_ITEM_NAME);
  return(0);
}


int main(const int argc, const char **argv) {
  LOAD_HASH_TABLE();
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  if (argc < 2) {
    return(print_help());
  }
  cmd = argv[1];

  if (strcmp(cmd, "sizes") == 0) {
    return(cmd_sizes());
  }
  if (strcmp(cmd, "names") == 0) {
    return(cmd_names());
  }

  return(print_help());
} /* main */
