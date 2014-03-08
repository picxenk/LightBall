/*******************************************************************
  LightBall
  http://xenbio.net/mdwiki/#!light_ball.md
  SeungBum Kim <picxenk@gmail.com>
*******************************************************************/

import processing.video.*;


/*******************************************************************
 Variables
*******************************************************************/
int BLEND_MODE = LIGHTEST;
boolean IS_FLIPPED = true;

Capture cam;
PImage canvas, canvas_back;

// fast computer: 800*600, slow computer: 640*480
int captureWidth = 640;
int captureHeight = 480;
int captureX = 0;
int captureY = 0;


/*******************************************************************
  Setup for Light Drawings
*******************************************************************/
void setup() {
  size(displayWidth, displayHeight);

  canvas = createImage(captureWidth, captureHeight, RGB);  
  canvas_back = createImage(captureWidth, captureHeight, RGB);
  
  cam = new Capture(this, captureWidth, captureHeight);  
  cam.start();
  cam.read();
  
  captureX = width/2-captureWidth/2;
  captureY = height/2-captureHeight/2;

  background(0);
}


/*******************************************************************
 Main Loop
*******************************************************************/
void draw() {
  if (cam.available() == true) {
    cam.read();
    cam.loadPixels();
    
    if (IS_FLIPPED) {
      canvas = flipCanvas(cam);
    } else {
      canvas = cam;
    }

    canvas_back.blend(canvas, 0, 0, captureWidth, captureHeight, 0, 0, captureWidth, captureHeight, BLEND_MODE);
    set(captureX, captureY, canvas_back);
  }
}


/*******************************************************************
 Key bindings
*******************************************************************/
void keyPressed() {
  if (key==' ') {
    saveCanvas();
    cam.start();
    cam.read();
    background(0);
    canvas_back = createImage(captureWidth, captureHeight, RGB);
    image(canvas_back, captureX, captureY, captureWidth, captureHeight);
  }
  if (key=='s') {
    saveCanvas();
  }
  if (key=='f') {
    if (IS_FLIPPED) IS_FLIPPED = false;
    else IS_FLIPPED = true;
  }
  
  // for filters
  if (key=='1') {
    filterDilate();
  }
  if (key=='2') {
    filterInvert();
  }
  if (key=='3') {
    filterGray();
  }
  if (key=='z') {
    cam.stop();
  }
}


/*******************************************************************
 Commands
*******************************************************************/
PImage flipCanvas(PImage cam) {
  int i=0;
  PImage canvas = createImage(captureWidth, captureHeight, RGB);
  for (int y=0; y<captureHeight; y++) {
    for (int x=captureWidth-1; x>=0; x--) {
      canvas.pixels[i] = cam.pixels[y*captureWidth + x];
      i++;
    }
  }
  return canvas;
} 


void saveCanvas() {
  String image_name;
  image_name = "./img/"+str(year())+str(month())+str(day())+"_"+str(hour())+str(minute())+str(second())+".png";
  canvas_back.save(image_name);
}


void filterGray() {
  cam.stop();
  canvas_back.filter(GRAY);
  canvas_back.filter(POSTERIZE, 9);
  set(captureX, captureY, canvas_back);
}


void filterInvert() {
  cam.stop();
  canvas_back.filter(INVERT);
  set(captureX, captureY, canvas_back);
}


void filterDilate() {
  cam.stop();
  canvas_back.filter(DILATE);
  set(captureX, captureY, canvas_back);
}
