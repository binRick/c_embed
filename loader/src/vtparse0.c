#include <stdio.h>
#include <string.h>
#include <vtparse/vtparse.h>


int main() {
  unsigned char *w;
  unsigned char *buf   = (unsigned char *)"[31m[1mok[22;39m";
  unsigned char *green = (unsigned char *)"[32m[1mok[22;39m";
  unsigned char *buf0  = (unsigned char *)"xxxxxxxxxxxxxxx";

  w = green;
  int                 l = strlen((const char *)w);

  unsigned int        buf_pos, did_read, i;
  unsigned char const *data;
  vtparse_t           parser;

  vtparse_init(&parser);
  buf_pos = 0;

  /* Parse the data and advance the cursor position */
  buf_pos += vtparse_parse(&parser, w + buf_pos, l - buf_pos);
  if (!vtparse_has_event(&parser)) {
    //break; /* No event to print, exit loop */
  }

  /* The parser returned, so there must be something interesting to
   * report! */
  printf("Received action %s\n", vtparse_action_str(parser.action));

  /* If data_end - data_begin > 0, there is a byte sequence that we
   * can process. This is relevent for VTPARSE_ACTION_PUT/
   * VTPARSE_ACTION_OSC_PUT/VTPARSE_ACTION_PRINT. For escape
   * sequences, the relevant letter is stored in "parser.ch" for
   * control sequences. */
  if (parser.data_begin != parser.data_end) {
    for (data = parser.data_begin; data < parser.data_end;
         data++) {
      printf("Char: 0x%02x ('%c')\n", *data, *data);
    }
  } else if (parser.ch != 0) {
    printf("Char: 0x%02x ('%c')\n", parser.ch, parser.ch);
  }

  /* Print any intermediate chars */
  if (parser.num_intermediate_chars > 0) {
    printf("%d Intermediate chars:\n",
           parser.num_intermediate_chars);
    for (i = 0; i < parser.num_intermediate_chars; i++) {
      printf("  0x%02x ('%c')\n", parser.intermediate_chars[i],
             parser.intermediate_chars[i]);
    }
  }

  /* Print any parameters */
  if (parser.num_params > 0) {
    printf("%d Parameters:\n", parser.num_params);
    for (i = 0; i < parser.num_params; i++) {
      printf("\t%d\n", parser.params[i]);
    }
  }
  printf("\n");

  return(0);
} /* main */

