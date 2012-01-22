#ifndef _JPoint_H_
#define _JPoint_H_

/**
   a class embodying a 3D cartesian coordinate, with limited trig
   support.
   @author jtnimoy
*/
class JPoint{
 public:
  float x;
  float y;
  float z;

  /**
     blank constructor - xyz set to 0
  */
  JPoint();

  /**
     construct with all 3 floats
     @param x
     @param y
     @param z
  */
  JPoint(float x,float y,float z);

  /**
     construct with JUST an x and y with Z defaulting to zero.
  */
  JPoint(float,float);
  
  
  /**
     construct with one common float. JPoint(34) is the same as saying
     JPoint(34,34,34) @param xyz
  */
  JPoint(float xyz);
  
  /**
     Goodbye, JPoint.
  */
  ~JPoint();

  
  /**
     rotate self about X axis by given radian degree about given pivot
  */
  void rotateSelfX(float deg,JPoint pivot);
  /**
     rotate self about Y axis by given radian degree about given pivot
  */
  void rotateSelfY(float deg,JPoint pivot);
  /**
     rotate self about Z axis by given radian degree about given pivot
  */
  void rotateSelfZ(float deg,JPoint pivot);

  /**
     return a new JPoint rotated about the X axis by radian degree about a given pivot.
  */
  JPoint rotateX(float deg,JPoint pivot);

  /**
     return a new JPoint rotated about the Y axis by radian degree about a given pivot.
  */
  JPoint rotateY(float deg,JPoint pivot);

  /**
     return a new JPoint rotated about the Z axis by radian degree about a given pivot.
  */
  JPoint rotateZ(float deg,JPoint pivot);


  /**
     return a new JPoint rotated about the X axis by radian degree with matrix origin as pivot.
  */
  JPoint rotateX(float deg);
  
  /**
     return a new JPoint rotated about the Y axis by radian degree with matrix origin as pivot.
  */
  JPoint rotateY(float deg);

  /**
     return a new JPoint rotated about the Z axis by radian degree with matrix origin as pivot.
   */
  JPoint rotateZ(float deg);

  /**
     get a 3D pythagorean distance between this JPoint and that JPoint
     @param thatPoint from which we are measuring distance to this object.
   */

  float distanceFrom(JPoint thatPoint);

  /**
     linear interpolate from the current position to a destination position.
     @param thatPoint - the destination point that we are measuring off of.
     @param lerpVal - some number between 0 and 1 - 0 being completely this and 1 being completely thatPoint.
  */
  JPoint lerpTo(JPoint thatPoint,float lerpVal);


  /**
     Like JPoint::lerpTo() except instead of returning a stack
     allocated JPoint, the operation is done to the object, itself.
  */
  
  void lerpSelfTo(JPoint p,float lerpVal);

  
  /**
     convenience function that tells the point to call glVertex3f(x,y,z);
  */
  void glVertex();

  /**
     convenience function that tells the point to call glTranslatef(x,y,z);
  */
  void glTranslate();

  /**
     copy the XYZ values from another JPoint
  */

  void copyFrom(JPoint);

  
  /**
     copy the XYZ values from three given floats x y and z.
  */
  void copyFrom(float,float,float);

  /**
     return the 2D atan2-based theta between this and another JPoint
  */

  float thetaFrom(JPoint p);

  JPoint operator+(JPoint);
  void operator+=(JPoint);
  void operator+=(JPoint*);//ha, start adding these in.
  void operator*=(JPoint);
  void operator*=(float);
  void operator/=(float);
  void operator-=(JPoint);
  JPoint operator*(JPoint);
  JPoint operator*(float);
  JPoint operator/(float);
  JPoint operator-(JPoint);

  /**
     swaps the XYZ values between two JPoint objects.
  */

  void swap(JPoint p);

  /**
     a cout wrapper that prints the XYZ on its own line.
  */
  
  void println();

  /**
     move away from another point by a certain absolute distance. Intended to suppliment lerpTo.
     this function returns a copy of the current object.
  */
  JPoint normalizeFrom(JPoint,float rad);

  /**
     move away from another point by a certain absolute distance. Intended to suppliment lerpTo.
     this does the operator to the current object.
  */
  
  void normalizeSelfFrom(JPoint,float rad);

  /**
     figure out what I am in window-space, which is different than OpenGL space.
  */
  void selfToWindowSpace();

  /**
     returns my distance from the origin.
  */
  float vectorLength();

  /**
     turns me into a useful unit vector.
   */
  void normalizeSelf();

  /**
     produce a dot product
   */
  float dotProductWith(JPoint that);

  /**
     produce a dot product
   */
  JPoint crossProductWith(JPoint that);

  /**
     return a point that has been forced into the positive 3D quadrant through sign inversions.
   */
  JPoint abs();

  JPoint invert();
  JPoint orientTo(JPoint p1, float zrot);
};



#endif

