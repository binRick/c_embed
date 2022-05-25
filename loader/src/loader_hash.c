/////////////////////////////////////////////
#include "../include/loader_hash.h"
#define BINARY_NAME    "loader_hash"


/////////////////////////////////////////////


static int print_help() {
  printf(
    "Usage:\n"
    "\t %s <command>\n\n"
    "Commands:\n"
    "\t debug:   debug hash table\n"
    "\t iterate: iterate embedded archive using djbhash\n",
    BINARY_NAME
    );
  return(1);
}


static int cmd_debug() {
  ITERATE_HASH(DEBUG_TBL_ITEM);
  return(0);
}


static int cmd_sizes() {
  ITERATE_HASH(DEBUG_TBL_ITEM_SIZE);
  return(0);
}


static int cmd_names() {
  ITERATE_HASH(DEBUG_TBL_ITEM_NAME);
  return(0);
}


static int cmd_json() {
  item = djbhash_iterate(&hash);
  int i;

  while (item && i < tbl_qty) {
    djbhash_print(item);
    item = djbhash_iterate(&hash);
  }
  return(0);
}


static int cmd_iterate() {
  /*
   * for (int i = 0; i < tbl_qty; i++) {
   * DEBUG_TBL_ITEM();
   * djbhash_set(&hash, tbl[i].filename, &i, DJBHASH_INT);
   * djbhash_set(&tbl_hash, tbl[i].filename, &tbl[i], DJBHASH_OTHER);
   * item = djbhash_find(&hash, tbl[i].filename);
   * djbhash_print(item);
   * item = djbhash_find(&tbl_hash, tbl[i].filename);
   * if (item != NULL) {
   * printf("#%d> |file:%s|size:%lub|\n",
   *       i,
   *       ((C_EMBED_TBL *)(item)->value)->filename,
   *       ((C_EMBED_TBL *)(item)->value)->size
   *       );
   * }
   * }
   */
  int i;

  djbhash_reset_iterator(&tbl_hash);
  item = djbhash_iterate(&tbl_hash);
  for (int i = 0; item; i++) {
    printf("#%d> |file:%s|size:%lub|\n",
           i,
           ((C_EMBED_TBL *)(item)->value)->filename,
           ((C_EMBED_TBL *)(item)->value)->size
           );
    item = djbhash_iterate(&tbl_hash);
  }
  djbhash_reset_iterator(&tbl_hash);

/*
 * unsigned char *json = djbhash_to_json(&hash);
 *
 * printf("JSON: %s\n", json);
 *
 * djbhash_dump(&hash);
 *
 *
 * free(json);
 * json = NULL;
 */
  djbhash_destroy(&tbl_hash);
  return(0);
} /* tbl_hash */


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
  if (strcmp(cmd, "debug") == 0) {
    return(cmd_debug());
  }
  if (strcmp(cmd, "json") == 0) {
    return(cmd_json());
  }
  if (strcmp(cmd, "iterate") == 0) {
    return(cmd_iterate());
  }

  return(print_help());
} /* main */
