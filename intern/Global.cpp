#include "Global.h"
#include "gl_et_al.h";
#include "jttoolkit.h";

Global *Global::instance;


Global::Global(){
  //glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  //glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
  //glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
  
  toggleFullScreen();
  
  mouseIsDown = false;
  
  instance=this; //making sure we store the global static instance pointer.
  
  world = dWorldCreate();
  //dWorldSetGravity (world, 0,0.1,0);
  infoVisible = true;
  physicsSpeed = 2;
  physicsSpeedClickCounter=110;  //start after the bounds of visibility

  mouseZCounter = 200;
  mouseZ = 0;

  justsaved = false;
  
  
  img = new Image("media/texture.png");
  
  //load custom colors
  Image *thisImg;
  thisImg = new Image("media/color/background.png");
  bgcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]); 
  
  thisImg = new Image("media/color/fill.png");
  fillcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]);

  thisImg = new Image("media/color/grid.png");
  gridcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]);

  thisImg = new Image("media/color/vertex.png");
  vertexcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]);
  
  thisImg = new Image("media/color/text.png");
  textcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]);
  
  thisImg = new Image("media/color/snapshot.png");
  snapcolor = new Color(thisImg->pixels[0],thisImg->pixels[1],thisImg->pixels[2]);
  
  
  showVerts = false;
  showGrid = false;
  showFaces = false;
  showTexture = true;
  showFill = true;

  fillOpacity = 0.5;

  glClearColor(bgcolor->red(),bgcolor->green(),bgcolor->blue(),1);

}




Global::~Global(){
  
}


void Global::loop(){
  
  //STEP
  dWorldStep(world,physicsSpeed);

  if(ticks()==0){
    cluster_width = 512;
    cluster_height = 512;
    cluster_skip = 4;
    for(int y=0;y<cluster_width;y+=cluster_skip){
      for(int x=0;x<cluster_height;x+=cluster_skip){
	dBodyID thisB = dBodyCreate(world);
	dBodySetPosition(thisB,x,y,0);
	bodies.push_back(thisB);
      }
    }
    resetAll();
    return;
  }



  
  //pull the masses towards the mouse while the mouse button is pressed
  if(mouseIsDown){
    
    deque<dBodyID>::iterator it;
    for(it=bodies.begin();it<bodies.end();it++){
      const dReal *pos = dBodyGetPosition(*it);
      dBodyID thisB = *it;
      JPoint vec(mouseX()-pos[0], mouseY()-pos[1],mouseZ);
      vec.normalizeSelf();
      vec*=0.1;
      dBodyAddForce(thisB,vec.x,vec.y,vec.z);
    }
    
  }
  
  

  

  //DRAW
   
  if(showTexture && showFill){
    //texture with vertex coordinates
    glBindTexture(GL_TEXTURE_2D, img->textureID);
    glColor4f(1,1,1,fillOpacity);
    int row = cluster_width/cluster_skip;
    for(int y=0;y<(cluster_height/cluster_skip)-1;y++){
      glBegin(GL_TRIANGLE_STRIP);
      for(int x=0;x<row;x++){
	const dReal *pos = dBodyGetPosition(bodies[y*row+x]);
	glTexCoord2f(x/(float)(cluster_width/cluster_skip),y/(float)(cluster_height/cluster_skip));
	glVertex3f(pos[0],pos[1],pos[2]);
	
	pos = dBodyGetPosition(bodies[(y+1)*row+x]);
	glTexCoord2f(x/(float)(cluster_width/cluster_skip),(y+1)/(float)(cluster_height/cluster_skip));
	glVertex3f(pos[0],pos[1],pos[2]);
      }
      glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, NULL);
  }




  
  
  if(showFaces && showFill){
    //flat faces
    glColor4f(fillcolor->red(),fillcolor->green(),fillcolor->blue(),fillOpacity);
    int row = cluster_width/cluster_skip;
    for(int y=0;y<(cluster_height/cluster_skip)-1;y++){
      glBegin(GL_TRIANGLE_STRIP);
      for(int x=0;x<row;x++){
	const dReal *pos = dBodyGetPosition(bodies[y*row+x]);
	glVertex3f(pos[0],pos[1],pos[2]);
	
	pos = dBodyGetPosition(bodies[(y+1)*row+x]);
	glVertex3f(pos[0],pos[1],pos[2]);
      }
      glEnd();
    }
  }

  if(showGrid){
    //grid
    glColor4f(gridcolor->red(),gridcolor->green(),gridcolor->blue(),0.2);
    int row = cluster_width/cluster_skip;
    for(int y=0;y<(cluster_height/cluster_skip)-1;y++){
      glBegin(GL_LINES);
      for(int x=0;x<row-1;x++){
	const dReal *pos1 = dBodyGetPosition(bodies[y*row+x]);
	const dReal *pos2 = dBodyGetPosition(bodies[(y+1)*row+x]);
	const dReal *pos3 = dBodyGetPosition(bodies[y*row+(x+1)]);
	const dReal *pos4 = dBodyGetPosition(bodies[(y+1)*row+(x+1)]);
	
	//left up-down
	glVertex3f(pos1[0],pos1[1],pos1[2]);
	glVertex3f(pos2[0],pos2[1],pos2[2]);
	
	//top left-right
	glVertex3f(pos1[0],pos1[1],pos1[2]);
	glVertex3f(pos3[0],pos3[1],pos3[2]);
	
	if(x==row-2){
	  //right up-down
	  glVertex3f(pos3[0],pos3[1],pos3[2]);
	  glVertex3f(pos4[0],pos4[1],pos4[2]);
	}
	
	if(y==(cluster_height/cluster_skip)-2){
	  //bottom left-right
	  glVertex3f(pos2[0],pos2[1],pos2[2]);
	  glVertex3f(pos4[0],pos4[1],pos4[2]);
	}
	
      }
      glEnd();
    }
  }


  if(showVerts){
    //vertexes
    glColor4f(vertexcolor->red(),vertexcolor->green(),vertexcolor->blue(),1.0);
    glBegin(GL_POINTS);
    deque<dBodyID>::iterator it;
    for(it=bodies.begin();it<bodies.end();it++){
      const dReal *pos = dBodyGetPosition(*it);
      glVertex3f(pos[0],pos[1],pos[2]);
    } 
    glEnd();
  }

  




  //text info display
  JoshFont *jf = getFont();
  
  if(infoVisible){
    glColor4f(0,0,0,1);
    glPushMatrix();
    glTranslatef(10,52,0);
    jf->drawString("PINCH\n\n\
gently click and drag\n\
TAB or ? show/hide this info\n\
ESC exists\n\
SPACE resets\n\
F toggles fullscreen\n\
\n\
UP increase mouseZ\n\
DOWN decrease mouseZ\n\
LEFT slow time\n\
RIGHT speed time\n\
\n\
ENTER stops the movement\n\
S saves an OBJ\n\
1 show/hide vertices\n\
2 show/hide grid\n\
3 toggle solid/textured fill\n\
4 show/hide fill\n\
\] increase fill/texture opacity\n\
\[ decrease fill/texture opacity\n\
\n\
jtnimoy, 2008\n\
",18,1);
    glPopMatrix();
  }
  
  if(physicsSpeedClickCounter<50){
    glColor4f(textcolor->red(),textcolor->green(),textcolor->blue(),1 - physicsSpeedClickCounter/50.0);
    glPushMatrix();
    glTranslatef(mouseX(),mouseY()+72,0);
    char displayStr[256];
    sprintf(displayStr,"%i steps",physicsSpeed);
    jf->drawString(displayStr,18,1);
    glPopMatrix();
  }
  
  if(mouseZCounter<50){
    glColor4f(textcolor->red(),textcolor->green(),textcolor->blue(),1 - mouseZCounter/50.0);
    glPushMatrix();
    glTranslatef(mouseX(),mouseY()+72+18,0);
    char displayStr[256];
    sprintf(displayStr,"%i mouseZ",mouseZ);
    jf->drawString(displayStr,18,1);
    glPopMatrix();
  }
  

  //indication that the save command was received and that the snapshot is taken
  if(justsaved){
    glColor4f(snapcolor->red(),snapcolor->green(),snapcolor->blue(),1);
    glLineWidth(10);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0,0);
    glVertex2f(width(),0);
    glVertex2f(width(),height());
    glVertex2f(0,height());
    glEnd();
    glLineWidth(1);
    justsaved = false;
  }

  physicsSpeedClickCounter++;
  mouseZCounter++;
}


void Global::keyDown(int k,int special){
  
  if(k=='f' && !special)toggleFullScreen();
  else if(k==' '){
    
    resetAll();
  }else if(k==102 && special){//up
    physicsSpeed++;
    physicsSpeedClickCounter=0;
  }else if(k==100 && special){//down
    physicsSpeed--;
    if(physicsSpeed<=0)physicsSpeed=1;
    physicsSpeedClickCounter=0;
  }else if (k=='s' || k=='S'){
    saveToObj();
    justsaved = true;
  }else if(k==13){
    //freeze scene
    deque<dBodyID>::iterator it;
    for(it=bodies.begin();it<bodies.end();it++){
      dBodyID thisB = *it;
      dBodySetForce(thisB,0,0,0);
      dBodySetTorque(thisB,0,0,0);
      dBodySetLinearVel(thisB,0,0,0);
      dBodySetAngularVel(thisB,0,0,0);
    }
  }else if(k=='\t' || k=='?' || k=='/'){
    infoVisible = !infoVisible;
  }else if((k==103) && special){//decrease mouseZ
    mouseZ --;
    mouseZCounter=0;
  }else if((k==101) && special){//increase mouseZ
    mouseZ++;
    mouseZCounter=0;
  }else if(k=='1'){
    showVerts = !showVerts;

  }else if(k=='2'){
    showGrid = !showGrid;

  }else if(k=='3'){
    showFaces = !showFaces;
    showTexture = !showFaces;//turn other one off
    
  }else if(k=='4'){
    showFill = !showFill;
  }else if(k==']'){
    fillOpacity+=0.1;
    if(fillOpacity>1)fillOpacity=1;
  }else if(k=='['){
    fillOpacity-=0.1;
    if(fillOpacity<0)fillOpacity=0;
  }
  /*
    else{
    cout << k << ' ' << special << endl;
  }
  */
}


void Global::mouseDown(){
  mouseIsDown = true;
}


void Global::mouseUp(){
  mouseIsDown = false;
}


void Global::resetAll(){
//reset all masses
  int i=0;
  float xmargin = (width()-cluster_width)/2;
  float ymargin = (height()-cluster_height)/2;
  for(int y=0;y<cluster_width;y+=cluster_skip){
    for(int x=0;x<cluster_height;x+=cluster_skip){
      dBodyID thisB = bodies[i];
      dBodySetPosition(thisB,xmargin+x,ymargin+y,0);
      dBodySetForce(thisB,0,0,0);
      dBodySetTorque(thisB,0,0,0);
      dBodySetLinearVel(thisB,0,0,0);
      dBodySetAngularVel(thisB,0,0,0);
      i++;
    }
  }
  physicsSpeedClickCounter = 200;
  physicsSpeed = 2;
  mouseZ = 1;
  mouseZCounter = 200;
}

void Global::saveToObj(){
  
  
//first check to see that it's not already there
  
  clock_t ct = clock();
  
  char fname[256];
  sprintf(fname,"pinch_output%05i.obj",ct);
  ofstream outfile(fname);
  
  outfile << "#Pinch OBJ export\n";
  outfile << "#www.jtnimoy.net\n";
  outfile << "o pinchmesh1\n";
  //lay down the vertices
  deque<dBodyID>::iterator it;
  for(it=bodies.begin();it<bodies.end();it++){
    const dReal *pos = dBodyGetPosition(*it);
    outfile << "v " << pos[0] << ' ' << pos[1] << ' ' << pos[2] << endl;
  }
  
  //lay down the face relationships

  outfile << "s 1\n";

  //flat faces
  int s = bodies.size();
  int row = cluster_width/cluster_skip;
  for(int y=0;y<(cluster_height/cluster_skip)-1;y++){
    for(int x=0;x<row-1;x++){
      outfile << "f "  << 
	1+y*row+x << ' ' << 
	1+(y+1)*row+x << ' ' << 
	1+(y+1)*row+(x+1) << ' ' << 
	1+y*row+(x+1) << '\n';
	
    }
  }
  
  
  
  
  outfile.close();
  
}


void Global::windowReshaped(int winX,int winY,int w,int h){

}
