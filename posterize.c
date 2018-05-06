#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void Posterization(Image *img);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
    exit(1);
  }

  Image *colorimg;

  if ((colorimg = Read_Bmp(argv[1])) == NULL) {
    exit(1);
  }

  Posterization(colorimg);

  if (Write_Bmp(argv[2], colorimg)) {
    exit(1);
  }

  Free_Image(colorimg);

  return 0;
}

void Posterization(Image *img) {
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      unsigned idx = i * img->width + j;

      // YUV conversion
      unsigned gray = 0.299 * img->data[idx].r + 0.587 * img->data[idx].g + 0.114 * img->data[idx].b;
      unsigned posterized;

      if (gray <= 64) {
        posterized = 0;
      } else if (gray > 64 && gray <= 128) {
        posterized = 85;
      } else if (gray > 128 && gray <= 192) {
        posterized = 170;
      } else if (gray > 192) {
        posterized = 255;
      }

      img->data[idx].r = img->data[idx].g = img->data[idx].b = posterized;
    }
  }
}

