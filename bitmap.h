// Almost copied from: http://hooktail.org/computer/index.php?plugin=attach&refer=Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB&openfile=bitmap.h

#ifndef __BITMAP_H_INCLUDED__
#define __BITMAP_H_INCLUDED__

#define FILEHEADERSIZE 14
#define INFOHEADERSIZE 40
#define HEADERSIZE (FILEHEADERSIZE + INFOHEADERSIZE)

typedef struct {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} Rgb;

typedef struct {
  unsigned int height;
  unsigned int width;
  Rgb *data;
} Image;

Image *Read_Bmp(char *filename);

int Write_Bmp(char *filename, Image *img);

Image *Create_Image(int width, int height);

void Free_Image(Image *img);

#endif /*__BITMAP_H_INCLUDED__*/

