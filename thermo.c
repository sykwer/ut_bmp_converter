#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void Thermoscale(Image *img);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;

    if ((colorimg = Read_Bmp(argv[1])) == NULL) {
        exit(1);
    }

    Thermoscale(colorimg);

    if (Write_Bmp(argv[2], colorimg)) {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

unsigned Redscale(unsigned gray) {
    if (gray <= 128) {
        return 0;
    } else if (gray > 128 && gray <= 192) {
        return 4 * (gray - 128);
    } else if (gray > 192) {
        return 255;
    }
}

unsigned Greenscale(unsigned gray) {
    if (gray <= 64) {
        return 4 * gray;
    } else if (gray > 64 && gray <= 192) {
        return 255;
    } else if (gray > 192) {
        return 255 - 4 * (gray - 192);
    }
}

unsigned Bluescale(unsigned gray) {
    if (gray <= 64) {
        return 255;
    } else if (gray > 64 && gray <= 192) {
        return 255 - 4 * (gray - 64);
    } else if (gray > 192) {
        return 0;
    }
}

void Thermoscale(Image *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            unsigned idx = i * img->width + j;

            // YUV conversion
            unsigned gray = 0.299 * img->data[idx].r + 0.587 * img->data[idx].g + 0.114 * img->data[idx].b;

            img->data[idx].r = Redscale(gray);
            img->data[idx].g = Greenscale(gray);
            img->data[idx].b = Bluescale(gray);
        }
    }
}

