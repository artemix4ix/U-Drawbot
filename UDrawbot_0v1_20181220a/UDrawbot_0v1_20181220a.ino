#include "PololuDriver.h"
#include "Ramps.h"

Ramps ramps = Ramps();
#include <Servo.h>

/*** define meseaures ***/
#define LEFT 0 //frame LEFT TOP (mm)
#define TOP 0 //frame TOP (mm)
#define WIDTH 530 //frame LEFT(mm)

//margin between the frame and canvas
#define marginL 100
#define marginT 100
#define marginR 100
//int marginB = 100;

//canvas size
#define canvasL LEFT + marginL
#define canvasT TOP + marginT
#define canvasW WIDTH-(marginL + marginR)
#define canvasH TOP+420

//position in coordination
#define homeX canvasL + canvasW/2
#define homeY canvasT + canvasH  //home position of gondola

boolean isDebug = true;

/*** default positions ***/
int x = 0, y = 0; //position of gondola
int px = x, py = y;//previous position of gondola
float tx = x, ty = y; //position of target location

//position in steps
long stepX, stepY; //position in motor steps
long stepTX, stepTY; //position in motor steps

//position in line length
float lineX, lineY; //position in line length
float lineTX, lineTY; //target position in line length
float lineDiffX, lineDiffY; //line length to change

//steps for given length
long lineDiff2stepsX, lineDiff2stepsY;

//cordination data
int data[2];
int index;

Servo pen;
int pos = 0; //up
int penUP = 180;
int penDOWN = 90;

String sample = "G1 X10 Y10 Z0 E12 F200 M140 S50";
String tempSample = "";
void setup() {
  Serial.begin(9600);
  //resetPosition();
  initPosition();
  pen.attach(11);
}

void loop () {
  if (Serial.available()) {
    char c = Serial.read();
    if (c != 10) {
      tempSample += c;
    } else if (c == 10) {
      //sample = tempSample;
      interpret(tempSample);
      tempSample = "";
    }

  }
  /*
    if (Serial.available() > 0) {
    char c = Serial.read();
    Serial.println(c);
    if (c == 'w') {
      moveUp(100);
    } else if (c == 's') {
      moveDown(100);
    } else if (c == 'r') {  // rect
      //moveTo(2000);
      moveToLoc(homeX, homeY - 50); //bottom center
      moveToLoc(homeX - 50, homeY - 50); //bottom left
      moveToLoc(homeX - 50, homeY - 100); //top left
      moveToLoc(homeX + 50, homeY - 100); //top right
      moveToLoc(homeX + 50, homeY - 50); //bottom right
      moveToLoc(homeX, homeY - 50); //bottom center
    } else if (c == 't') {  // triangle
      //moveTo(2000);
      int y1 = 150;
      int y2 = 210;
      moveToLoc(homeX, homeY - y1); //bottom center
      moveToLoc(homeX - 70, homeY - y1); //bottom left
      moveToLoc(homeX, homeY - y2); //top center
      moveToLoc(homeX + 70, homeY - y1); //bottom right
      moveToLoc(homeX, homeY - y1); //bottom center
    } else if (c == 'p') {  // triangle
      pen.write(penDOWN);
    } else if (c == 'l') {  // triangle
      pen.write(penUP); //
    } else if (c == 'q') {
      resetPosition();
    } else if (c >= '0' && c <= '9') {
      int i = c - '0';
      data[index] = data[index] * 10 + i;
    } else if (c == ',') {
      index++;
    }
    else if (c == '\n') {
      digitalWrite(X_ENABLE_PIN, LOW); // HIGH --> disable outputs
      digitalWrite(Y_ENABLE_PIN, LOW); // HIGH --> disable outputs
      digitalWrite(Z_ENABLE_PIN, LOW); // HIGH --> disable outputs
      moveToLoc(data[0], data[1]);

      data[0] = 0;
      data[1] = 0;
      index = 0;
    }
    }
  */



  /*
    moveToLoc(homeX, homeY - 200);
    for (int i = -100; i < 100; i++) {
    moveToLoc(homeX + i * 2, homeY - 200);
    }
    for (int i = 100; i > -100; i--) {
    moveToLoc(homeX + i * 2, homeY - 200);
    }
    moveToLoc(homeX, homeY - 200);
  */
  /*
    //draw rect
    goTo(30, 30);

    //draw rect
    goTo(10, 10);
    goTo(50, 10);
    goTo(50, 30);
    goTo(10, 30);
    goTo(10, 10);

    //draw hex
    //goTo(10, 10);
    goTo(30, 10);
    goTo(50, 20);
    goTo(50, 30);
    goTo(30, 40);
    goTo(10, 30);
    goTo(10, 20);
    goTo(30, 10);
  */
}
