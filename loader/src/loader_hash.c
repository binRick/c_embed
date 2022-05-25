/////////////////////////////////////////////
#include "../src/includes.c"
/////////////////////////////////////////////
#include "../embeds/tbl1.embed"
#include "../submodules/djbhash/src/djbhash.h"
/////////////////////////////////////////////
static char *cmd;


/////////////////////////////////////////////
static int print_help() {
  printf(
    "Usage:\n"
    "\t loader1 <command>\n\n"
    "Commands:\n"
    "\t hash: show embedded archive using hash approach\n"
    );

  return(1);
}


static int tbl_hash() {
  struct djbhash      hash, tbl_hash;
  struct djbhash_node *item;

  djbhash_init(&hash);
  djbhash_init(&tbl_hash);

  for (int i = 0; i < tbl_qty; i++) {
    printf("#%d> Loaded %6lu bytes- %20s|\n", i, tbl[i].size, tbl[i].filename);
    djbhash_set(&hash, tbl[i].filename, &i, DJBHASH_INT);
    djbhash_set(&tbl_hash, tbl[i].filename, &tbl[i], DJBHASH_OTHER);
    item = djbhash_find(&hash, tbl[i].filename);
    djbhash_print(item);
    item = djbhash_find(&tbl_hash, tbl[i].filename);
    if (item != NULL) {
      printf("#%d> |file:%s|size:%lub|\n",
             i,
             ((C_EMBED_TBL *)(item)->value)->filename,
             ((C_EMBED_TBL *)(item)->value)->size
             );
    }
  }
  item = djbhash_iterate(&hash);
  while (item) {
    djbhash_print(item);
    item = djbhash_iterate(&hash);
  }

  djbhash_reset_iterator(&hash);
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


  unsigned char *json = djbhash_to_json(&hash);

  printf("JSON: %s\n", json);

  djbhash_dump(&hash);


  free(json);
  json = NULL;

  djbhash_destroy(&hash);
  return(0);
} /* tbl_hash */


int main(const int argc, const char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  if (argc < 2) {
    return(print_help());
  }

  cmd = argv[1];

  if (strcmp(cmd, "hash") == 0) {
    return(tbl_hash());
  }
  return(print_help());
} /* main */
