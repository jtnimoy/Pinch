/**
   wrapper include for openGL interested includers.
   so i don't have to multiply update all opengl includings each time i switch plats.
*/

#if defined(__DARWIN__)
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
#else
  #include <GL/glut.h>
  #include <GL/gl.h>
#endif

