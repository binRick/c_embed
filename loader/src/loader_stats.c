/////////////////////////////////////////////
#include "../include/loader_stats.h"
#define BINARY_NAME    "loader_stats"


/////////////////////////////////////////////


static int print_help() {
  printf(
    "Usage:\n"
    "\t %s <command>\n\n"
    "Commands:\n"
    "\t qty:        table qty\n"
    "\t timestamp:  table timestamp\n"
    "\t size:       table size\n",
    BINARY_NAME
    );
  return(1);
}


static int cmd_qty() {
  printf("%lu\n", tbl_qty);
  return(0);
}


static int cmd_timestamp() {
  printf("%llu\n", tbl_created_ts);
  return(0);
}


static int cmd_size() {
  printf("%lu\n", tbl_bytes);
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

  if (strcmp(cmd, "qty") == 0) {
    return(cmd_qty());
  }
  if (strcmp(cmd, "size") == 0) {
    return(cmd_size());
  }
  if (strcmp(cmd, "timestamp") == 0) {
    return(cmd_timestamp());
  }

  return(print_help());
} /* main */
