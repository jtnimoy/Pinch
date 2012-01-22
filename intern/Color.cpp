#include "Color.h"
#include "jttoolkit.h"
#include "Global.h"


Color::Color(char r,char g,char b){
  _red = (unsigned char)r/255.0;
  _green = (unsigned char)g/255.0;
  _blue = (unsigned char)b/255.0;
}

Color::Color(float r,float g,float b){
  _red = r;
  _green = g;
  _blue = b;
}

Color::Color(){
  _red = 0;
  _green = 0;
  _blue = 0;
}

Color::~Color(){

}

float Color::red(){
  return _red;
}

float Color::green(){
  return _green;
}

float Color::blue(){
  return _blue;
}

