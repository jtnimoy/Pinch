#include "JRect.h"
#include "jttoolkit.h"
#include "Global.h"

void JRect::copyFrom(JRect t){
  x1=t.x1;
  y1=t.y1;
  x2=t.x2;
  y2=t.y2;
  
}

JRect JRect::operator+(JRect t){
  return JRect(
	       x1+t.x1,
	       y1+t.y1,
	       x2+t.x2,
	       y2+t.y2
	       );
}


JRect JRect::operator+(JPoint t){
  return JRect(
	       x1+t.x,
	       y1+t.y,
	       x2+t.x,
	       y2+t.y
	       );
}


void JRect::operator+=(JPoint that){
  x1+=that.x;
  x2+=that.x;
  y1+=that.y;
  y2+=that.y;
}

JRect::JRect(float xx1,float yy1,float xx2,float yy2){
  x1=xx1;
  y1=yy1;
  x2=xx2;
  y2=yy2;
}

bool JRect::intersects(JRect that){
  /*
  return pointInside(JPoint(that.x1,that.y1)) ||
    pointInside(JPoint(that.x2,that.y2)) || 
    pointInside(JPoint(that.x1,that.y2)) ||
    pointInside(JPoint(that.x2,that.y1)) ||
    that.pointInside(JPoint(x1,y1)) || 
    that.pointInside(JPoint(x2,y2)) ||
    that.pointInside(JPoint(x1,y2)) ||
    that.pointInside(JPoint(x2,y1)) ;
  */
  JRect r1(*this);
  JRect r2(that);
  r1.axisAlign();
  r2.axisAlign();
  return !((r1.x2<r2.x1 || r1.x1>r2.x2) || (r1.y2<r2.y1 || r1.y1>r2.y2));
    
}

JRect::JRect(){
  x1=0;
  y1=0;
  x2=0;
  y2=0;
}

JRect::JRect(float *f){
  loadMem(f);
}

JRect::JRect(int *f){
  loadMem(f);
}


void JRect::loadMem(float *f){
  x1=f[0];
  y1=f[1];
  x2=f[2];
  y2=f[3];
}


void JRect::loadMem(int *f){
  x1=f[0];
  y1=f[1];
  x2=f[2];
  y2=f[3];
}

JRect::~JRect(){

}

bool JRect::pointInside(JPoint *p){
  return pointInside(*p);
}

bool JRect::pointInside(JPoint p){
  return ( ((p.x >= x1) && (p.x <= x2)) || ((p.x <= x1) && (p.x >= x2))  ) && 
         ( ((p.y >= y1) && (p.y <= y2)) || ((p.y <= y1) && (p.y >= y2))  );
}

void JRect::operator*=(float v){
  x1*=v;
  y1*=v;
  x2*=v;
  y2*=v;
}


void JRect::glRect(){
  glRectf(x1,y1,x2,y2);
  
  /*
  glPointSize(3);
  glBegin(GL_POINTS);
  glColor4f(1,0,0,0.5);
  glVertex2f(x1,y1);
  glColor4f(0,0,1,0.5);
  glVertex2f(x2,y2);
  glEnd();
  glPointSize(1);
  glColor4f(1,1,1,0.5);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x1,y1);
  glVertex2f(x1,y2);
  glVertex2f(x2,y2);
  glVertex2f(x2,y1);
  glEnd();
  */
}


void JRect::axisAlign(){
  float t;
  if(x1>x2){
    t=x1;
    x1=x2;
    x2=t;
  }
  if(y1>y2){
    t=y1;
    y1=y2;
    y2=t;
  }
}


void JRect::println(){
  cout << "JRect( " << x1 << " , " << y1 << " , " << x2 << " , " << y2 << " )" << endl;
}

float JRect::getWidth(){
  return fabs(x1-x2);
}

float JRect::getHeight(){
  return fabs(y1-y2);
}


JPoint JRect::getCenter(){
  return JPoint(
		(x1+x2)/2.0,
		(y1+y2)/2.0
		);
}


void JRect::bisect(JRect rr,JRect *s1,JRect *s2,bool orientation){
  JRect r(rr);
  r.axisAlign();
  if(orientation){
    s1->x1 = r.x1;
    s1->y1 = r.y1;
    s1->x2 = r.x1+r.getWidth()/2;
    s1->y2 = r.y2;

    s2->x1 = r.x1+r.getWidth()/2;
    s2->y1 = r.y1;
    s2->x2 = r.x2;
    s2->y2 = r.y2;
  }else{
    s1->x1 = r.x1;
    s1->y1 = r.y1;
    s1->x2 = r.x2;
    s1->y2 = r.y1+r.getHeight()/2;
    
    s2->x1 = r.x1;
    s2->y1 = r.y1+r.getHeight()/2;
    s2->x2 = r.x2;
    s2->y2 = r.y2;
    
  }
}



void JRect::glVertex(){
  point().glVertex();
}


JPoint JRect::point(){
  return (JPoint(x1,y1)+JPoint(x2,y2))*0.5;
}
