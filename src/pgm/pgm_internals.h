#include "include/pgm.h"

extern struct pgm *parse_header(FILE *f);
extern void write_header(FILE *f, struct pgm *image);

extern char skip_whitespaces(FILE *f);

extern void read_bytes_simple(FILE *f, struct pgm *image);
extern void read_bytes_double(FILE *f, struct pgm *image);
extern void write_bytes_simple(FILE *f, struct pgm *image);
extern void write_bytes_double(FILE *f, struct pgm *image);
