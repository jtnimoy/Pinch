#ifndef _Color_H_
#define _Color_H_


class Color{
 public:
  Color(char r,char g, char b);
  Color(float r,float g, float b);
  Color();
  ~Color();
  float red();
  float green();
  float blue();
 private:
  float _red;
  float _green;
  float _blue;
};



#endif

