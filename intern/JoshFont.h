#ifndef _JOSHFONT_H_
#define _JOSHFONT_H_

#include <fstream.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include "JPoint.h"
using namespace std;


#if defined(__DARWIN__)
#include <GLUT/glut.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ttnameid.h>
#include <freetype/ftglyph.h>
#elif defined(linux)
#include <GL/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ttnameid.h>
#include <freetype/ftglyph.h>
#endif


#include <string.h>

#define JF_VECTOR 0
#define JF_BITMAP 1


/**
   a freetype2 wrapper used by jttoolkit as PFont mirrored support, although
   it provides various other unusual layout support. True type font
   files are supported. Letterforms are rendered to screen as little
   textures. I believe there used to also be support for vector-based
   true type rendering, but I may have commented all that code out
   over the years. It's a pretty messy class that has travelled with
   me over time. Also see jttoolkit::getFont()

   @code
   //in this example, jttoolkit has already instantiated a JoshFont with the file "media/usethis.ttf"
   //and so we are retreiving a pointer to that and using it to render some text in space.
   JoshFont*f = getFont();
   glColor3f(1,1,1); //color the text
   mouse().glTranslate(); //glTranslate over to where ever the mouse is.
   f->drawString("hi there",20,1); //tell the default system font to draw
   @endcode
   
   @author jtnimoy
*/
class JoshFont{
public:
  
  /**
     construct a new JoshFont instance.
     @param file a filename of a true type font.
     @param lettersize the size of the textures
     @param renderstyle vector or raster?
     @param antialiased which only applies to raster texture technique.
     @param mipmap whether or not to use the totally awesome smoothing mipmapping that opengl does that we love so much
  */
  JoshFont(char file[], int lettersize=80,int renderstyle=JF_BITMAP, int antialiased=true,int mipmap=true);
  ~JoshFont();
  
  
  int base;
  int textures[256];
  float charWidths[256];
  float charHeights[256];
  float charHoriBearingYs[256];
  float charHoriBearingXs[256];
  float charHoriAdvances[256];
  float charVertBearingYs[256];
  float charVertBearingXs[256];
  float charVertAdvances[256];
  float*feedbackBuffers[256];
  int feedbackSizes[256];
  float units_per_EM;
  float ascender;
  float descender;
  float text_height;
  float initsize;
  int rendermode;
  FT_Library ft_library;
  FT_Face ft_face;
  
  /**
     used to store initial window values. of what? i do not recall
  */
  float feedbackScale;
  
  /**

  */
  void drawTriangleChar(char c,float size);

  /**

  */
  void initFeedback();

  /**

  */
  int open(char file[], int lettersize,int renderStyle, int antialiased,int mipmap);
  
  /**

  */
  void drawChar(char c);
  
  /**
     
  */
  void tessChar(char c,float lettersize);
  
  /**
     
  */
  void feedbackChar(char c,float lettersize);
  
  /**
     draw a string as simple as can be. Usually preceded with a call to glTranslate.
     @param inputstr the text to draw
     @param size font size
     @param tracking line break spacing size 
  */



  void getDrawStringPositions(char *inputstr,float size,float tracking,deque<JPoint> *positions);


  void drawString(char *inputstr,float size,float tracking);
  
  /**
     draw a string paragraph-wrapped inside a box
     @param inputstr the text to draw
     @param size font size
     @param tracking vertical spacing between lines
     @param right rect width
     @param bottom rect height
     @param quickrender a boolean choosing whether to render the paragraph as just blocks for faster preview.
  */
  void drawStringBoxWrap(char *inputstr,float size,float tracking,float right,float bottom,int quickrender);
  
  /**
     draw a string and stretch it so that it will fit inside a rect. The rect is assued to be cornered at 0,0,right,bottom
     @param inputstr the text to draw
     @param right right X value of the rect
     @param bottom lower Y value of the rect
  */
  void drawStringFittedBox(char *inputstr,float right,float bottom);
  
  /**
     get the width of a string at a give size.
     @param inputstr the the copy to use to layout the type
     @param size the font size to measure by
     
  */
  float getStringWidth(char *inputstr, int size);
  
  /**
     load a single bitmap char into a texture and return the opengl textureID.
     @param buffer some pixels
     @param imageWidth the image width
     @param imageHeight the image height
     @param srcWidth the source width (i'm not sure what that means)
     @param srcHeight the source height (i'm not sure what that means)
     @param mipmap a boolean specifying whether or not to mipmap.
  */
  int loadBitmapCharRAWFromMemory(void*buffer,
				  int imageWidth, int imageHeight,
				  int srcWidth, int srcHeight,int mipmap);
  
  
  /**
     my own personal randomFloat for no real reason other than legacy
     and porting laziness. please ignore.
   */
  float randomFloat();
};

#endif

