#ifndef _JRect_H_
#define _JRect_H_

#include "JPoint.h"

/**
   rectangular geometry and open gl convenience object. cousin of JPoint
*/
class JRect{
 public:
  
  float x1; ///< left
  float y1; ///< top
  float x2; ///< right
  float y2; ///< bottom
  JRect(); ///< empty constructor initialises zero'd memory
  JRect(float *buff); ///< construct off a 4-part float array
  JRect(int *buff); ///< construct off a 4-part int array
  JRect( float x1 , float y1 , float x2 , float y2 ); ///< construct from floats left/top/right/bottom 
  void loadMem(float *buff); ///< copy values from an array
  void loadMem(int *buff);  ///< copy values from an array
  ~JRect(); ///< goodbye JRect
  void glRect(); ///< convenience function
  bool pointInside(JPoint p); ///< is that JPoint inside me?
  bool pointInside(JPoint *p); ///< is that JPoint pointer inside me?
  
  void operator*=(float v);
  void operator+=(JPoint);
  JRect operator+(JRect);
  JRect operator+(JPoint);

  bool intersects(JRect that); ///< do I intersect with some other rectangle?
  void axisAlign(); ///< make sure x1 is to the left and that y1 is above.
  
  void copyFrom(JRect); ///< copy my values from another JRect
  void println(); ///< print my values to the console
  float getWidth(); ///< get the delta between x1 and x2
  float getHeight(); ///< get the delta between y1 and y2
  JPoint getCenter(); ///< get the centre point of the rectangle.
  void bisect(JRect r,JRect *s1,JRect *s2,bool orientation); ///< cut the rectangle in half and return the pieces as two new jrects.
  void glVertex(); ///< convenience function for openGL rendering - one vertex from the centre point.
  JPoint point(); ///< returns a centre point
};



#endif

