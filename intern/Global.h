#ifndef _Global_H_
#define _Global_H_

#include <deque>
#include <ode/ode.h>;
#include "Image.h";
#include "Color.h";

using namespace std;

class Global{
 public:
  
  static Global*instance; ///< sort of like _global or _root in flash so you can say Global::instance->drips from anywhere.
  void loop(); ///< the loop callback called by the system. Equiv to Processing draw()
  void keyDown(int k,int special); ///< catch a keyDown event by populating this function with creative code!
  void mouseDown(); ///< catch a mouseDown event by populating this function with creative code!
  void mouseUp();///< catch a mouseUp event.
  void windowReshaped(int winX,int winY,int w,int h);
  Global();
  ~Global();
  dWorldID world;
  deque<dBodyID> bodies;
  bool mouseIsDown;
  int cluster_width;
  int cluster_height;
  int cluster_skip;
  void resetAll();
  bool infoVisible;
  int physicsSpeed;
  int physicsSpeedClickCounter;
  void saveToObj();
  int mouseZCounter;
  int mouseZ;
  bool justsaved;
  Image *img;
  Color *bgcolor;
  Color *fillcolor;
  Color *gridcolor;
  Color *vertexcolor;
  Color *textcolor;
  Color *snapcolor;

  bool showVerts;
  bool showFaces;
  bool showGrid;
  bool showTexture;
  bool showFill;
  float fillOpacity;
};

#endif

