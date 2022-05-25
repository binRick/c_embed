/////////////////////////////////////////////
#include "../include/loader_list.h"
#define BINARY_NAME    "loader_list"
/////////////////////////////////////////////
static char *cmd;


static int tbl_info() {
  printf("Loaded %lu files:\n", tbl_qty);
  for (int i = 0; i < tbl_qty; i++) {
    printf("#%d> Loaded %6lu bytes- %20s|\n", i, tbl[i].size, tbl[i].filename);
  }
  return(0);
}


/////////////////////////////////////////////
static int print_help() {
  printf(
    "Usage:\n"
    "\t %s <command>\n\n"
    "Commands:\n"
    "\t info: show embedded archive information\n",
    BINARY_NAME
    );

  return(1);
}


int main(const int argc, const char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  if (argc < 2) {
    return(print_help());
  }

  cmd = argv[1];

  if (strcmp(cmd, "info") == 0) {
    return(tbl_info());
  }

  return(print_help());
} /* main */
