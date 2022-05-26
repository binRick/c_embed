#include "../include/embed.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#define VERSION         "v0.3"
#define MAX_FILENAME    256

typedef struct {
  FILE          *fp;
  unsigned char buf[4096];
  int           idx;
  int           eof_idx;
} BufferedFile;

size_t  total_bytes, qty;
int64_t ts;
char    uuid4[UUID4_LEN];
char    unique[UUID4_LEN];


static BufferedFile bf_writer(FILE *fp) {
  BufferedFile bf = { .fp = fp };

  return(bf);
}


static BufferedFile bf_reader(FILE *fp) {
  BufferedFile bf = { .fp = fp, .idx = sizeof(bf.buf), .eof_idx = -1 };

  return(bf);
}


static void bf_flush(BufferedFile *bf) {
  fwrite(bf->buf, 1, bf->idx, bf->fp);
  bf->idx = 0;
}


static void bf_write_byte(BufferedFile *bf, char b) {
  bf->buf[bf->idx++] = b;
  if (bf->idx == sizeof(bf->buf)) {
    bf_flush(bf);
  }
}


static int bf_read_byte(BufferedFile *bf) {
  if (bf->idx == sizeof(bf->buf)) {
    int n = fread(bf->buf, 1, sizeof(bf->buf), bf->fp);
    if (n != sizeof(bf->buf)) {
      bf->eof_idx = n;
    }
    bf->idx = 0;
  }
  if (bf->idx == bf->eof_idx) {
    return(EOF);
  }
  return(bf->buf[bf->idx++]);
}


static void error(const char *fmt, ...) {
  va_list vp;

  fprintf(stderr, "Error: ");
  va_start(vp, fmt);
  vfprintf(stderr, fmt, vp);
  va_end(vp);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}


static void safename(char *dst, const char *filename) {
  const char *p = filename;
  char       *q = dst;

  while (*p) {
    if (isalpha(*p) || isdigit(*p)) {
      *q = *p;
    } else {
      *q = '_';
    }
    q++; p++;
  }
  *q = '\0';
}


static void write_byte_string(BufferedFile *bf, unsigned char n) {
  if (n >= 100) {
    bf_write_byte(bf, '0' + (n / 100) % 10);
  }
  if (n >= 10) {
    bf_write_byte(bf, '0' + (n / 10) % 10);
  }
  bf_write_byte(bf, '0' + n % 10);
  total_bytes++;
}


static void write_embedded(FILE *fp, const char *filename,
                           const char *varprefix, int nostatic, int zerobyte){
  FILE *infp = fopen(filename, "rb");

  if (!infp) {
    error("failed to open file '%s'", filename);
  }

  char varname[MAX_FILENAME];

  if (strlen(filename) >= MAX_FILENAME) {
    error("filename too long");
  }
  safename(varname, filename);

  if (!nostatic) {
    fprintf(fp, "static ");
  }
  fprintf(fp, "unsigned char __C_EMBED_TBL__%s__%s%s[] = {", unique, varprefix, varname);
  BufferedFile inbf = bf_reader(infp);
  BufferedFile bf   = bf_writer(fp);
  int          n    = 0;

  for ( ;;) {
    int chr = bf_read_byte(&inbf);
    if (chr == EOF) {
      break;
    }
    if (n > 0) {
      bf_write_byte(&bf, ',');
    }
    if (n % 20 == 0) {
      bf_write_byte(&bf, '\n');
      bf_write_byte(&bf, '\t');
    }
    write_byte_string(&bf, chr);
    n++;
  }

  bf_flush(&bf);
  if (zerobyte) {
    fprintf(fp, ",0");
  }
  fprintf(fp, "\n};\n\n");

  fclose(infp);
} /* write_embedded */


static void print_help(void) {
  printf(
    "Usage: embed [OPTION]... [FILE]...\n"
    "Create C header with file data embedded in char arrays\n"
    "\n"
    "  -o <filename>  output file\n"
    "  -p <prefix>    prefix to place before variable names\n"
    "  -s             omit `static` keyword\n"
    "  -z             add zero byte to end of array\n"
    "  -t <name>      create table of { filename, data, size }\n"
    "  -h             display this help message\n"
    "  -v             display version number\n");
}


int main(int argc, char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  char **arg     = argv + 1;
  char **arg_end = argv + argc;

  /* defaults */
  ts = timestamp();
  uuid4_init();
  uuid4_generate(uuid4);
  safename(unique, uuid4);

  struct StringFNStrings uuid_split = stringfn_split(uuid4,'-');
  char *uuid_mini = strdup(uuid_split.strings[0]);
  safename(unique, uuid_mini); 

  const char *outfile   = NULL;
  const char *prefix    = "";
  const char *tablename = NULL;
  int        zerobyte   = 0;
  int        nostatic   = 0;

  /* handle options */
  while (arg != arg_end && (*arg)[0] == '-') {
    switch ((*arg)[1]) {
    case 'h':
      print_help();
      exit(EXIT_SUCCESS);
      break;

    case 'v':
      printf("embed " VERSION "\n");
      exit(EXIT_SUCCESS);
      break;

    case 's':
      nostatic = 1;
      break;

    case 'z':
      zerobyte = 1;
      break;

    case 't':
      arg++;
      if (arg == arg_end) {
        error("expected name after option '-t'");
      }
      tablename = *arg;
      break;

    case 'o':
      arg++;
      if (arg == arg_end) {
        error("expected filename after option '-o'");
      }
      outfile = *arg;
      break;

    case 'p':
      arg++;
      if (arg == arg_end) {
        error("expected prefix after option '-p'");
      }
      prefix = *arg;
      break;

    default:
      error("invalid option '%s'", *arg);
      break;
    } /* switch */

    arg++;
  }

  /* no file arguments: print help */
  if (arg == arg_end) {
    print_help();
    exit(EXIT_SUCCESS);
  }

  /* open output */
  FILE *fp = outfile ? fopen(outfile, "wb") : stdout;

  if (!fp) {
    error("failed to open output file '%s'", outfile);
  }
  fprintf(fp, "#pragma once\n");
  fprintf(fp, "#include <stdio.h>\n");
  fprintf(fp, "#include <ctype.h>\n");
  fprintf(fp, "#include <string.h>\n");
  fprintf(fp, "#include <stdlib.h>\n\n");
  fprintf(fp, "#ifndef __C_EMBED_TBL__DEFINED\n#define __C_EMBED__TBL__DEFINED\n");
  fprintf(fp, "typedef struct C_EMBED_TBL C_EMBED_TBL;\nstruct C_EMBED_TBL { \n\tchar *filename; \n\tunsigned char *data; \n\tsize_t size;\n};\n#endif\n\n");

  /* write files */
  for (char **a = arg; a < arg_end; a++) {
    write_embedded(fp, *a, prefix, nostatic, zerobyte);
  }

  /* write table */
  if (tablename) {
    if (!nostatic) {
      fprintf(fp, "static ");
    }
    fprintf(fp, "C_EMBED_TBL %s[] = {\n", tablename);
    for (char **a = arg; a < arg_end; a++) {
      char varname[MAX_FILENAME];
      safename(varname, *a);
      fprintf(fp, "\t{\n\t\t.filename = \"%s\",\n\t\t.data     = __C_EMBED_TBL__%s__%s,\n\t\t.size     = (size_t)sizeof(__C_EMBED_TBL__%s__%s)",
              *a, unique, varname, unique, varname
              );
      if (zerobyte) {
        fprintf(fp, " - 1,\n");
      }
      fprintf(fp, "\t},\n");
      qty++;
    }
    fprintf(fp, "\t{ NULL },\n");
    fprintf(fp, "};\n\n"
            "size_t %s_qty = %lu;\n"
            "size_t %s_bytes = %lu;\n"
            "int64_t %s_created_ts = %lld;\n",
            tablename, qty,
            tablename, total_bytes,
            tablename, ts
            );
  }

  /* clean up */
  if (fp != stdout) {
    fclose(fp);
  }
  return(EXIT_SUCCESS);
} /* main */
