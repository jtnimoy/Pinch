#include "JPoint.h"
#include "gl_et_al.h"
#include "math.h"
#include <iostream>
#include "jttoolkit.h"

using namespace std;


void JPoint::println(){
  cout << "JPoint(" << x << " , " << y << " , " << z << ")" << endl;
}


void JPoint::rotateSelfX(float deg,JPoint pivot){
  copyFrom(rotateX(deg,pivot));
}

void JPoint::rotateSelfY(float deg,JPoint pivot){
  copyFrom(rotateY(deg,pivot));
}

void JPoint::rotateSelfZ(float deg,JPoint pivot){
  copyFrom(rotateZ(deg,pivot));
}




JPoint JPoint::rotateX(float deg){
  rotateX(deg,JPoint(0));
}

JPoint JPoint::rotateY(float deg){
  rotateY(deg,JPoint(0));
}

JPoint JPoint::rotateZ(float deg){
  rotateZ(deg,JPoint(0));
}
/*
JPoint JPoint::rotateX(float deg,JPoint pivot){
  float xd = x-pivot.x;
  float yd = y-pivot.y;
  float zd = z-pivot.z;
  float r = sqrt(zd*zd+yd*yd);
  float theta = atan2(y-pivot.y,z-pivot.z)+deg;
  return JPoint(
		x,
		r*sin(theta),
		r*cos(theta)
		)+pivot;
}
*/
JPoint JPoint::rotateX(float deg,JPoint pivot){
	float xd = x-pivot.x;
	float yd = y-pivot.y;
	float zd = z-pivot.z;
	float r = sqrt(zd*zd+yd*yd);
	float theta = atan2(yd,zd)+deg;
	return JPoint(
		x,
		y+(r*sin(theta)-yd),
		z+(r*cos(theta)-zd));
}

/*
JPoint JPoint::rotateY(float deg,JPoint pivot){
  float xd = x-pivot.x;
  float yd = y-pivot.y;
  float zd = z-pivot.z;
  float r = sqrt(xd*xd+zd*zd);
  float theta = atan2(z-pivot.z,x-pivot.x) + deg;
  return JPoint(
		r*cos(theta),
		y,
		r*sin(theta)
		)+pivot;
}
*/
JPoint JPoint::rotateY(float deg,JPoint pivot){
	float xd = x-pivot.x;
	float yd = y-pivot.y;
	float zd = z-pivot.z;
	float r = sqrt(xd*xd+zd*zd);
	float theta = atan2(zd,xd) + deg;
	return JPoint(
		x+(r*cos(theta)-xd),
		y,
		z+(r*sin(theta)-zd));
}


JPoint JPoint::rotateZ(float deg,JPoint pivot){
  float xd = x-pivot.x;
  float yd = y-pivot.y;
  float zd = z-pivot.z;
  float r = sqrt(xd*xd+yd*yd);
  float theta = atan2(yd,xd) + deg;
  return JPoint(
		r*cos(theta),
		r*sin(theta),
		z)+pivot;
}


JPoint JPoint::lerpTo(JPoint p,float lerpVal){
  return (*this)+(p-(*this))*lerpVal;
}


void JPoint::lerpSelfTo(JPoint p,float lerpVal){
  JPoint pp = (*this)+(p-(*this))*lerpVal;
  copyFrom(pp);
}


JPoint::JPoint(){
  x=0;
  y=0;
  z=0;
}

JPoint::JPoint(float xx,float yy,float zz){
  x=xx;
  y=yy;
  z=zz;
}

JPoint::JPoint(float xx,float yy){
  x=xx;
  y=yy;
  z=0;
}

JPoint::JPoint(float v){
  x=v;
  y=v;
  z=v;
}

JPoint::~JPoint(){
  
}

void JPoint::glVertex(){
  glVertex3f(x,y,z);
}

void JPoint::glTranslate(){
  glTranslatef(x,y,z);
}


void JPoint::copyFrom(JPoint p){
  x=p.x;
  y=p.y;
  z=p.z;
}


void JPoint::copyFrom(float xx,float yy,float zz){
  x=xx;
  y=yy;
  z=zz;
}



float JPoint::thetaFrom(JPoint p){
  float xd = p.x-x;
  float yd = p.y-y;
  return atan2(yd,xd);
}


JPoint JPoint::operator+(JPoint p){
  return JPoint(p.x+x,p.y+y,p.z+z);
}


JPoint JPoint::operator-(JPoint p){
  return JPoint(x-p.x,y-p.y,z-p.z);
}


void JPoint::operator+=(JPoint p){
  x+=p.x;
  y+=p.y;
  z+=p.z;
}


void JPoint::operator+=(JPoint* p){
  x+=p->x;
  y+=p->y;
  z+=p->z;
}


void JPoint::operator*=(JPoint p){
  x*=p.x;
  y*=p.y;
  z*=p.z;
}

void JPoint::operator*=(float f){
  x*=f;
  y*=f;
  z*=f;
}

void JPoint::operator/=(float f){
  x/=f;
  y/=f;
  z/=f;
}

void JPoint::operator-=(JPoint p){
  x-=p.x;
  y-=p.y;
  z-=p.z;
}

JPoint JPoint::operator*(JPoint p){
  return JPoint(p.x*x,p.y*y,p.z*z);
}

JPoint JPoint::operator*(float v){
  return JPoint(x*v,y*v,z*v);
}

JPoint JPoint::operator/(float v){
  return JPoint(x/v,y/v,z/v);
}



void JPoint::swap(JPoint p){
  float tx = x;
  float ty = y;
  float tz = z;
  x=p.x;
  y=p.y;
  z=p.z;
  p.x = tx;
  p.y = ty;
  p.z = tz;
}


float JPoint::distanceFrom(JPoint p){
  float xd = p.x-x;
  float yd = p.y-y;
  float zd = p.z-z;
  return sqrt(xd*xd+yd*yd+zd*zd);
}



/**
   move a point away from another point in order to satisfy a minimum radius.
*/
JPoint JPoint::normalizeFrom(JPoint that,float rad){
  JPoint p(*this);
  float bulbosity_correction = -(rad - distanceFrom(that))/rad;
  p.lerpSelfTo(that,bulbosity_correction);
  return p;
}



/**
   move self away from another point in order to satisfy a minimum radius.
*/
void JPoint::normalizeSelfFrom(JPoint that,float rad){
  float r = distanceFrom(that);
  float t = thetaFrom(that);
  copyFrom(that);
  x += rad * cos(t);
  y += rad * sin(t);
}

void JPoint::selfToWindowSpace(){
  GLdouble model[16];
  GLdouble proj[16];
  GLint view[4];
  GLdouble retX;
  GLdouble retY;
  GLdouble retZ;
  
  glGetDoublev(GL_PROJECTION_MATRIX, proj);
  glGetDoublev(GL_MODELVIEW_MATRIX, model);
  glGetIntegerv (GL_VIEWPORT, view);
  
  gluProject(x,y,z,
	     (const GLdouble*)model,
	     (const GLdouble*)proj,
	     (const GLint*)view,
	     &retX,&retY,&retZ);
  
  x = retX;
  y = height()-retY;
  z = 0;
}

float JPoint::vectorLength(){
  return sqrt(x*x+y*y+z*z);
}


void JPoint::normalizeSelf(){
  (*this)/=vectorLength();
}

float JPoint::dotProductWith(JPoint that){
  return acos(x * that.x + y * that.y + z * that.z);
}

JPoint JPoint::crossProductWith(JPoint that){
  JPoint cross;
  cross.x = y * that.z - z * that.y;
  cross.y = z * that.x - x * that.z;
  cross.z = x * that.y - y * that.x;
  return cross;
}

JPoint JPoint::abs(){
  JPoint p(*this);
  p.x=fabs(p.x);
  p.y=fabs(p.y);
  p.z=fabs(p.z);
  return p;
}


JPoint JPoint::invert(){
  JPoint p(*this);
  p.x = -x;
  p.y = -y;
  p.z = -z;
  return p;
}

/**
   @author Keith Pasko
*/

JPoint JPoint::orientTo(JPoint p1, float zrot){ 
  JPoint* p2 = this; 
  // Calculate values to degrees.
  //float xrot = -(asin((y-p1.y)/(this->distanceFrom(1))));
  float xrot = -(asin((y-p1.y)/(this->distanceFrom(p1))));
  float yrot = atan2((x-p1.x), (z-p1.z));
  return JPoint (xrot,yrot,zrot);
}
