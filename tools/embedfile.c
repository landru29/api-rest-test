#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

FILE* open_or_exit(const char* fname, const char* mode)
{
  FILE* f = fopen(fname, mode);
  if (f == NULL) {
    perror(fname);
    exit(EXIT_FAILURE);
  }
  return f;
}

int main(int argc, char** argv)
{
  if (argc < 4) {
    fprintf(stderr, "USAGE: %s {sym} {rsrc} {name}\n\n"
        "  Creates {sym}.c from the contents of {rsrc}\n",
        argv[0]);
    return EXIT_FAILURE;
  }

  const char* sym = argv[1];
  FILE* in = open_or_exit(argv[2], "r");

  char symfile[500];

  snprintf(symfile, sizeof(symfile), "%s.h", sym);

  FILE* out = open_or_exit(symfile,"w");
  fprintf(out, "const char %s[] = {\n", argv[3]);

  char buf[256];
  size_t nread = 0;
  size_t linecount = 0;
  do {
    nread = fread(buf, 1, sizeof(buf), in);
    size_t i;
    for (i=0; i < nread; i++) {
      if (buf[i]>=0) {
        fprintf(out, "0x%02x, ", buf[i]);
      } else {
        fprintf(out, "-0x%02x, ", -buf[i]);
      }
      if (++linecount == 10) { fprintf(out, "\n"); linecount = 0; }
    }
  } while (nread > 0);
  if (linecount > 0) fprintf(out, "\n");
  fprintf(out, "};\n");
  fprintf(out, "const size_t %s_len = sizeof(%s);\n\n",argv[3],argv[3]);

  fclose(in);
  fclose(out);

  return EXIT_SUCCESS;
}