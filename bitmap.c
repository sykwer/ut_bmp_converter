// Almost copied from: http://hooktail.org/computer/index.php?plugin=attach&refer=Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB&openfile=bitmap.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bitmap.h"

Image *Read_Bmp(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Error: %s could not be read.", filename);
        return NULL;
    }

    unsigned char header_buf[HEADERSIZE];
    fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp);

    if (strncmp(header_buf, "BM", 2)) {
        fprintf(stderr, "Error: %s is not bitmap file.", filename);
        return NULL;
    }

    unsigned int width, height, color;
    memcpy(&width, header_buf + 18, sizeof(width));
    memcpy(&height, header_buf + 22, sizeof(height));
    memcpy(&color, header_buf + 28, sizeof(unsigned int));

    if (color != 24) {
        fprintf(stderr, "Error: %s is not bitmap file.", filename);
        return NULL;
    }

    int real_width = width * 3 + width % 4;
    unsigned char *bmp_line_data;

    if ((bmp_line_data = (unsigned char *) malloc(sizeof(unsigned char) * real_width)) == NULL) {
        fprintf(stderr, "Error: Allocation error\n");
        return NULL;
    }

    Image *img;
    if ((img = Create_Image(width, height)) == NULL) {
        free(bmp_line_data);
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        fread(bmp_line_data, 1, real_width, fp);

        for (int j = 0; j < width; j++) {
            img->data[(height - i - 1) * width + j].b = bmp_line_data[j * 3];
            img->data[(height - i - 1) * width + j].g = bmp_line_data[j * 3 + 1];
            img->data[(height - i - 1) * width + j].r = bmp_line_data[j * 3 + 2];
        }
    }

    free(bmp_line_data);
    fclose(fp);

    return img;
}

int Write_Bmp(char *filename, Image *img) {
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "Error: %s could not be open.", filename);
        return 1;
    }

    int real_width = img->width * 3 + img->width % 4;
    unsigned int file_size = img->height * real_width + HEADERSIZE;

    // config
    unsigned int offset_to_data = HEADERSIZE;
    unsigned int info_header_size = INFOHEADERSIZE;
    unsigned int planes = 1;
    unsigned int color = 24;
    unsigned long compress = 0;
    unsigned long data_size = img->height * real_width;
    long xppm = 1;
    long yppm = 1;

    // construct header
    unsigned char header_buf[HEADERSIZE];
    header_buf[0] = 'B';
    header_buf[1] = 'M';
    memcpy(header_buf + 2, &file_size, sizeof(file_size));

    for (int i = 6; i <= 9; i++) {
        header_buf[i] = 0;
    }

    memcpy(header_buf + 10, &offset_to_data, sizeof(file_size));

    for (int i = 11; i <= 13; i++) {
        header_buf[i] = 0;
    }

    memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));

    for (int i = 15; i <= 17; i++) {
        header_buf[i] = 0;
    }

    memcpy(header_buf + 18, &img->width, sizeof(img->width));
    memcpy(header_buf + 22, &img->height, sizeof(img->height));
    memcpy(header_buf + 26, &planes, sizeof(planes));
    memcpy(header_buf + 28, &color, sizeof(color));
    memcpy(header_buf + 30, &compress, sizeof(compress));
    memcpy(header_buf + 34, &data_size, sizeof(data_size));
    memcpy(header_buf + 38, &xppm, sizeof(xppm));
    memcpy(header_buf + 42, &yppm, sizeof(yppm));

    for (int i = 46; i <= 53; i++) {
        header_buf[i] = 0;
    }

    fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);

    unsigned char *bmp_line_data;

    if ((bmp_line_data = (unsigned char *) malloc(sizeof(unsigned char) * real_width)) == NULL) {
        fprintf(stderr, "Error: Allocation error\n");
        return 1;
    }

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            bmp_line_data[j * 3] = img->data[(img->height - i - 1) * img->width + j].b;
            bmp_line_data[j * 3 + 1] = img->data[(img->height - i - 1) * img->width + j].g;
            bmp_line_data[j * 3 + 2] = img->data[(img->height - i - 1) * img->width + j].r;
        }

        for (int j = img->width * 3; j < real_width; j++) {
            bmp_line_data[j] = 0;
        }

        fwrite(bmp_line_data, sizeof(unsigned char), real_width, fp);
    }

    free(bmp_line_data);
    fclose(fp);

    return 0;
}

Image *Create_Image(int width, int height) {
    Image *img;

    if ((img = (Image *) malloc(sizeof(Image))) == NULL) {
        fprintf(stderr, "Allocation error.\n");
        return NULL;
    }

    if ((img->data = (Rgb *) malloc(sizeof(Rgb) * width * height)) == NULL) {
        fprintf(stderr, "Allocation error.\n");
        free(img);
        return NULL;
    }

    img->width = width;
    img->height = height;

    return img;
}

void Free_Image(Image *img) {
    free(img->data);
    free(img);
}
