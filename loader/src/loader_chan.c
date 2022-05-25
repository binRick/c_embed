/////////////////////////////////////////////
#include "../include/loader_chan.h"
#define BINARY_NAME    "loader_chan"
/////////////////////////////////////////////
static char *cmd;


char *b64(const char *s) {
  char *enc = b64_encode((const unsigned char *)s, strlen(s));

  return(enc);
}

chan_t *chan;


void * ping(){
  char *msg = b64("ok");

  chan_send(chan, msg);
  return(NULL);
}


int cmd_chan(){
  chan = chan_init(0);
  pthread_t th;

  pthread_create(&th, NULL, ping, NULL);
  void *msg;

  chan_recv(chan, &msg);
  unsigned char *dec = b64_decode((const char *)msg, strlen((const char *)msg));

  printf("recvd:   %s -> %s\n", (const char *)msg, (const char *)dec);
  chan_dispose(chan);
  return(0);
}


static int tbl_list() {
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
    "\t chan: chan embedded archive files\n",
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

  if (strcmp(cmd, "chan") == 0) {
    return(cmd_chan());
  }

  return(print_help());
} /* main */
