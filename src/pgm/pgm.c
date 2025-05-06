#include "include/pgm.h"
#include <ctype.h>
#include <stdlib.h>


/* INTERNALS  */

/*skips 0 or more whitespaces upcoming in the stream
  and returns the next non-whitespace character.*/
char skip_whitespaces(FILE *f) {
  char c = fgetc(f);
  while (isspace(c))
    c = fgetc(f);
  return c;
}


struct pgm *parse_header(FILE *f) {
  char c, _;
  uint16_t width = 0;
  uint16_t height = 0;
  uint16_t max_gray = 0;
  char swidth[6];
  char sheight[6];
  char smax_gray[6];

  /*  ignore "P5". */
  do {
    c = fgetc(f);
  } while (!isspace(c));
  c = skip_whitespaces(f);

  // parse width
  int i = 0;
  while (!isspace(c)) {
    swidth[i] = c;
    i++;
    c = fgetc(f);
  }
  swidth[i] = 0;
  width = atoi(swidth);

  c = skip_whitespaces(f);

  // parse height
  i = 0;
  while (!isspace(c)) {
    sheight[i] = c;
    i++;
    c = fgetc(f);
  }
  sheight[i] = 0;
  height = atoi(sheight);

  c = skip_whitespaces(f);

  // parse max_gray
  i = 0;
  while (!isspace(c)) {
    smax_gray[i] = c;
    i++;
    c = fgetc(f);
  }
  smax_gray[i] = 0;
  max_gray = atoi(smax_gray);

  struct pgm *res = malloc(sizeof(struct pgm));

  res->height = height;
  res->width = width;
  res->max_gray = max_gray;
  return res;
}


void write_header(FILE *f, struct pgm *image) {
  char swidth[6];
  char sheight[6];
  char smax_gray[6];
  
  fputc('P', f);
  fputc('5', f);
  fputc('\n', f);

  sprintf(swidth, "%d", image->width);
  sprintf(sheight, "%d", image->height);
  sprintf(smax_gray, "%d", image->max_gray);

  fputs(swidth, f);
  fputc(' ', f);
  fputs(sheight, f);
  fputc('\n', f);
  fputs(smax_gray, f);
  fputc('\n', f);
}

void write_bytes_simple(FILE *f, struct pgm *image) {
  for (int i = 0; i<image->height; i++) {
    for (int j = 0; j<image->width; j++) {
      fputc(image->rows[i][j], f);
    }
  }
}

void write_bytes_double(FILE *f, struct pgm *image) {
  for (int i = 0; i<image->height; i++) {
    for (int j = 0; j<image->width; j++) {
      char upper = image->rows[i][j]/256;
      char lower = image->rows[i][j]%256;
      fputc(upper, f);
      fputc(lower, f);
    }
  }
}

void read_bytes_simple(FILE *f, struct pgm *image) {
  image->rows = malloc(image->height * sizeof(uint16_t *));
  for (int i = 0; i<image->height; i++) {
    image->rows[i] = malloc(image->width * sizeof(uint16_t));
    for (int j = 0; j<image->width; j++) {
      image->rows[i][j] = fgetc(f);
    }
  }
}


void read_bytes_double(FILE *f, struct pgm *image) {
  image->rows = malloc(image->height * sizeof(uint16_t *));
  for (int i = 0; i<image->height; i++) {
    image->rows[i] = malloc(image->width * sizeof(uint16_t));
    for (int j = 0; j<image->width; j++) {
      image->rows[i][j] = fgetc(f);
      image->rows[i][j] <<= 8;
      image->rows[i][j] += fgetc(f);
    }
  }
}


/* MATRIX/PGM INTERFACE */

struct pgm *matrix_to_pgm(struct matrix *a, uint16_t max_gray) {
  uint16_t width, height;
  struct pgm *res = malloc(sizeof(struct pgm));

  width = a->n;
  height = a->m;

  res->width = width;
  res->height = height;
  res->max_gray = max_gray;

  res->rows = malloc(res->height * sizeof(uint16_t *));
  for (int i = 0; i<height; i++) {
    res->rows[i] = malloc(res->width * sizeof(uint16_t));
    for (int j = 0; j<width; j++) {
      res->rows[i][j] = a->weights[i*width + j];
    }
  }

  return res;
}

struct matrix *pgm_to_matrix(struct pgm *image) {
  struct matrix *res = matrix_new(image->width, image->height);

  for (int i = 0; i<res->m; i++) {
    for (int j = 0; j<res->n; j++) {
      res->weights[i*res->n + j] = image->rows[i][j];
    }
  }

  return res;
}


/* PGM/IMAGE INTERFACE */

void pgm_to_image(struct pgm *image, const char *filename) {
  FILE *f = fopen(filename, "w");
  write_header(f, image);

  if (image->max_gray<256) {
    write_bytes_simple(f, image);
  } else {
    write_bytes_double(f, image);
  }
  fclose(f);
}

struct pgm *image_to_pgm(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Could not open specified file: %s\n", filename);
  }
  
  struct pgm *image = parse_header(f);
  if (image->max_gray < 256) {
    read_bytes_simple(f, image);
  } else {
    read_bytes_simple(f, image);
  }
  fclose(f);

  return image;
}
