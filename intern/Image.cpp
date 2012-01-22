#include "Image.h"
extern "C"{
#include "pngLoad.h"
}

Image::Image(){
  
}

void Image::load(char*filename){
  
  unsigned long *pwidth, *pheight;
  int result;
  
  result = pngLoad(filename, &pwidth, &pheight, &pixels);
  
  if (result == 0){
    printf("(pngLoad) %s FAILED.\n", filename);
  }
  _width  = (unsigned long)pwidth;
  _height = (unsigned long)pheight;

  reverseRowOrder();
  generateTexture();
}

void Image::draw(){
  glPushMatrix();
  glScalef(_width,_height,0);
  glCallList(listID);
  glPopMatrix();
}

Image::Image(char*filename){
  load(filename);
}

Image::~Image(){
  
}

unsigned long Image::width(){
  return _width;
}

unsigned long Image::height(){
  return _height;
}


void Image::generateTexture(){
  
  //CREATE TEXTURE
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, _width,_height,GL_RGB, GL_UNSIGNED_BYTE, pixels );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width,_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
  
  //USE TEXTURE TO MAKE A DISPLAY LIST
  listID = glGenLists(1);
  glNewList(listID, GL_COMPILE);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  
  //ratio may not be square.
  
  float w;
  float h;
  
  w=1;
  h=1;
  
  glBegin(GL_QUADS);
  glTexCoord2f(0,0);glVertex2f(0,0);	
  glTexCoord2f(1,0);glVertex2f(w,0);
  glTexCoord2f(1,1);glVertex2f(w,h);
  glTexCoord2f(0,1);glVertex2f(0,h);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D,0);
  glEndList();
  glBindTexture(GL_TEXTURE_2D,0);
  
  
}

void Image::reverseRowOrder(){
  //RGB
  int components = 3;
  
  char *destbuff = new char[_width*_height*components];
  
  //swap top with bottom
  for(int y=0;y<_height;y++){
    for(int x=0;x<_width;x++){
      destbuff[y*_width*components+x*components+0]=pixels[(_height-y-1)*_width*components+x*components+0];
      destbuff[y*_width*components+x*components+1]=pixels[(_height-y-1)*_width*components+x*components+1];
      destbuff[y*_width*components+x*components+2]=pixels[(_height-y-1)*_width*components+x*components+2];
    }
  }
    delete [] pixels;
    pixels = destbuff;
    
}

