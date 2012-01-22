#ifndef _JColor_H_
#define _JColor_H_

/**
   the beginnings of a class to handle color.
   so far, 0 is black and 1 is white.
   @author jtnimoy
*/
class JColor{
 public:
  float r; ///< red channel
  float g; ///< green channel
  float b; ///< blue channel
  float a; ///< alpha channel
  JColor(float r,float g,float b,float a); ///< construct a new color with explicit rgba
  JColor(float r,float g,float b); ///< construct a color and assume the alpha is 100% non-transparent
  JColor(float); ///< construct a 100% non-transparent gray value.
  JColor(); ///< make a default color (black)
  ~JColor();
  void glColor(); ///< convenience opengl rendering function. This calls glColor4f
  void contrast(float); ///< pumps the contrast a bit. Written for GRL graffitti brush.
};



#endif

