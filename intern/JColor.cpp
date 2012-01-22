#include "JColor.h"
#include "jttoolkit.h"
#include "Global.h"


JColor::JColor(float rr,float gg,float bb,float aa){
  r = rr;
  g = gg;
  b = bb;
  a = aa;
}

JColor::JColor(float rr,float gg,float bb){
  r = rr;
  g = gg;
  b = bb;
  a = 1;
}

JColor::JColor(float v){
  r = v;
  g = v;
  b = v;
  a = 1;
}

JColor::JColor(){
  r = 0;
  g = 0;
  b = 0;
  a = 1;
}

JColor::~JColor(){

}

void JColor::glColor(){
  glColor4f(r,g,b,a);
}


void JColor::contrast(float v){

#define bringCloser(x)  \
           if(x>0.5)x+=(1-x)*v;  \
           else     x+=(0-x)*v;

  bringCloser(r);
  bringCloser(g);
  bringCloser(b);
  bringCloser(a);
  
#undef bringCloser

}
