#ifndef _Image_H_
#define _Image_H_

#include "gl_et_al.h"


class Image{
 public:
  Image();
  Image(char*filename);
  void load(char*filename);
  ~Image();
  unsigned long width();
  unsigned long height();
  void draw();
  char *pixels;
  GLuint textureID;
  unsigned int listID;
 private:
  unsigned long _width;
  unsigned long _height;
  void generateTexture();
  void reverseRowOrder();
};



#endif

