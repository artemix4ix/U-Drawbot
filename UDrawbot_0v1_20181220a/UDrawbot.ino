#define stepsPERmm 76.92307 * 3 //20000 / 260
#define mmPERstep 0.013 //260 / 20000

//void updatePosition() {
//  stepX = ramps.motorX.position;
//  stepY = ramps.motorY.position;
//}
void initPosition() {
  x = homeX;
  y = homeY;
  tx = x;
  ty = y;
  lineX = dist(LEFT, TOP, x, y);
  lineY = dist(LEFT + WIDTH, TOP, LEFT + WIDTH - x, y);
  lineTX = lineX;
  lineTY = lineY;
  lineDiffX = lineTX - lineX;
  lineDiffY = lineTY - lineY;
  lineDiff2stepsX = lineDiffX * stepsPERmm;
  lineDiff2stepsY = lineDiffY * stepsPERmm;

  ramps.motorX.position = lineX * stepsPERmm;
  ramps.motorY.position = lineY * stepsPERmm;

  stepX = ramps.motorX.position;
  stepY = ramps.motorY.position;
  stepTX = stepX;
  stepTY = stepY;

  ramps.motorX.setDir(1);
  ramps.motorY.setDir(1);
  ramps.motorZ.setDir(1);

  digitalWrite(X_ENABLE_PIN, HIGH); // HIGH --> disable outputs
  digitalWrite(Y_ENABLE_PIN, HIGH); // HIGH --> disable outputs
  digitalWrite(Z_ENABLE_PIN, HIGH); // HIGH --> disable outputs

  Serial.println("#### initPosition()");
  printInfo();
  Serial.println("-------------------------");
}
void resetPosition() {
  x = px;
  y = py;
  tx = x;
  ty = y;
  lineX = dist(LEFT, TOP, x, y);
  lineY = dist(LEFT + WIDTH, TOP, LEFT + WIDTH - x, y);
  lineTX = lineX;
  lineTY = lineY;
  lineDiffX = lineTX - lineX;
  lineDiffY = lineTY - lineY;
  lineDiff2stepsX = lineDiffX * stepsPERmm;
  lineDiff2stepsY = lineDiffY * stepsPERmm;

  ramps.motorX.position = lineX * stepsPERmm;
  ramps.motorY.position = lineY * stepsPERmm;

  stepX = ramps.motorX.position;
  stepY = ramps.motorY.position;
  stepTX = stepX;
  stepTY = stepY;

  digitalWrite(X_ENABLE_PIN, LOW); // HIGH --> disable outputs
  digitalWrite(Y_ENABLE_PIN, LOW); // HIGH --> disable outputs
  digitalWrite(Z_ENABLE_PIN, LOW); // HIGH --> disable outputs

  Serial.println("#### resetPosition()");
  printInfo();
  Serial.println("-------------------------");
}
float dist(float tx, float ty, float x, float y) {
  float d = sqrt(pow(tx - x, 2) + pow(ty - y, 2));
  return d;
}
void moveUp(int distance) {
  //ramps.moveTo(stepX + distance, (stepY - distance), 0, 500);
  ramps.moveTo(stepX + distance, stepY - distance, 0, 300);
  stepX = ramps.motorX.position;
  stepY = ramps.motorY.position;
  //  updatePosition();
  Serial.println("move UP: x=0, y = 100");
  moveToLoc(homeX, 300) ;
  printLocs();
  printSteps();
  //distance--;
}
void moveDown(int distance) {
  //  ramps.moveTo(stepX - distance, stepY + distance, 0, 500);
  ramps.moveTo(stepX - distance, stepY + distance, 0, 500);
  stepX = ramps.motorX.position;
  stepY = ramps.motorY.position;
  //  updatePosition();
  Serial.println("move DOWN: x=0, y = -100");
  moveToLoc(homeX, homeY);
  printLocs();
  printSteps();
  //distance++;
}
void moveToLoc(float _tx, float _ty) {
  tx = _tx;
  ty = _ty;

  lineX = dist(LEFT, TOP, x, y);
  lineY = dist(LEFT + WIDTH, 0, LEFT + WIDTH - x, y);
  lineTX = dist(LEFT, TOP, tx, ty);
  lineTY = dist(LEFT + WIDTH, 0, LEFT + WIDTH - tx, ty);
  lineDiffX = lineTX - lineX;
  lineDiffY = lineTY - lineY;
  lineDiff2stepsX = lineDiffX * stepsPERmm;
  lineDiff2stepsY = lineDiffY * stepsPERmm;

  ////////////////////////////////////////////
  //calibrate arc
  //  float angle = WIDTH * 3.14 / WIDTH * 1.0;
  //  Serial.print("angle=");
  //  Serial.println(angle);
  ////////////////////////////////////////////
  //  printLineDiff2Steps();

  Serial.println("#### moveToLoc()");
  printInfo();
  ramps.moveTo(stepX - lineDiff2stepsX, stepY + lineDiff2stepsY, 0, 300);
  stepX = ramps.motorX.position;
  stepY = ramps.motorY.position;
  px = x;
  py = y;
  x = tx;
  y = ty;
  Serial.println("-------------------------");
}

void steps2locs() {
  int _x = stepX * mmPERstep;
  int _y = stepY * mmPERstep;
  //  printSteps2Locs();
  Serial.print("current stepX to locs=");
  Serial.print(_x);
  Serial.print(", stepY to locs =");
  Serial.println(_y);
}
void getLineLength() {
  lineX = dist(0, 0, x, y);
  lineY = dist(WIDTH, 0, x, y);
  //  printLength();
  Serial.print("current lineX=");
  Serial.print(lineX);
  Serial.print(", lineY=");
  Serial.println(lineY);
}

void getTargetLineLength(float _tx, float _ty) {
  lineTX = dist(0, 0, _tx, _ty);
  lineTY = dist(WIDTH, 0, _tx, _ty);
  //  printTargetLineLength() ;
  Serial.print("target _tx=");
  Serial.print(_tx);
  Serial.print(", _ty=");
  Serial.print(_ty);
  Serial.print(", lineTX=");
  Serial.print(lineTX);
  Serial.print(", lineTY=");
  Serial.println(lineTY);
}
void getLineDiff() {
  lineDiffX = lineTX - lineX;
  lineDiffY = lineTY - lineY;
  //  printLineDiff();
  Serial.print("lineDiffX=");
  Serial.print(lineDiffX);
  Serial.print(", lineDiffY=");
  Serial.println(lineDiffY);
}
void getDiff2Steps() {
  lineDiff2stepsX = lineDiffX * stepsPERmm;
  lineDiff2stepsY = lineDiffY * stepsPERmm;
  //  printLineDiff2Steps();
  Serial.print("lineDiff2stepsX to steps=");
  Serial.print(lineDiff2stepsX);
  Serial.print(", lineDiff2stepsY to steps =");
  Serial.println(lineDiff2stepsY);
}
void printSteps() {
  Serial.print("current stepX=");
  Serial.print(stepX);
  Serial.print(", stepY=");
  Serial.println(stepY);
}
void printLocs() {
  Serial.print("current x=");
  Serial.print(x);
  Serial.print(", y=");
  Serial.println(y);
}
void printLength() {
  Serial.print("current lineX=");
  Serial.print(lineX);
  Serial.print(", lineY=");
  Serial.println(lineY);
}
void printTargetLineLength() {
  Serial.print("target lineTX=");
  Serial.print(lineTX);
  Serial.print(", lineTY=");
  Serial.println(lineTY);
}
//void printLineDiff() {
//  Serial.print("target diffX=");
//  Serial.print(diffX);
//  Serial.print(", diffY=");
//  Serial.println(diffY);
//}
//void printLineDiff2Steps() {
//  Serial.print("target diffX to steps=");
//  Serial.print(len2stepsX);
//  Serial.print(", diffY to steps =");
//  Serial.println(len2stepsY);
//}
//void printSteps2Locs() {
//  Serial.print("target diffX to steps=");
//  Serial.print(len2stepsX);
//  Serial.print(", diffY to steps =");
//  Serial.println(len2stepsX);
//}

void printInfo() {
  int lineNum = 0;
  // line 0
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.println("init()");
  // line 1
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("LEFT=");
  Serial.print(LEFT);
  Serial.print(", WIDTH=");
  Serial.println(WIDTH);
  // line 2
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("homeX=");
  Serial.print(homeX);
  Serial.print(", homeY=");
  Serial.println(homeY);
  // line 3
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("x=");
  Serial.print(x);
  Serial.print(", y=");
  Serial.println(y);
  // line 4
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("tx=");
  Serial.print(tx);
  Serial.print(", ty=");
  Serial.println(ty);
  // line 5
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("stepX=");
  Serial.print(stepX);
  Serial.print(", stepY=");
  Serial.println(stepY);
  // line 6
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("stepTX=");
  Serial.print(stepTX);
  Serial.print(", stepTY=");
  Serial.println(stepTY);
  // line 7
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("lineX=");
  Serial.print(lineX);
  Serial.print(", lineY=");
  Serial.println(lineY);
  // line 8
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("lineTX=");
  Serial.print(lineTX);
  Serial.print(", lineY=");
  Serial.println(lineTY);
  // line 9
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("lineDiffX=");
  Serial.print(lineDiffX);
  Serial.print(", lineDiffY=");
  Serial.println(lineDiffY);
  // line 10
  lineNum++;
  Serial.print("[");
  Serial.print(lineNum);
  Serial.print("]");
  lineNum++;
  Serial.print("lineDiff2stepsX=");
  Serial.print(lineDiff2stepsX);
  Serial.print(", lineDiff2stepsY=");
  Serial.println(lineDiff2stepsY);
}
