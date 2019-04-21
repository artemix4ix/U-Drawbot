/*
  N3 T0*57
  N4 G92 E0*67
  N5 G28*22
  N6 G1 F1500.0*82
  N7 G1 X2.0 Y2.0 F3000.0*85
  N8 G1 X3.0 Y3.0*33
*/
//https://www.simplify3d.com/support/articles/3d-printing-gcode-tutorial/

//String sample = "G1 X10 Y10 Z0 E12 F200 M140 S50";
//G-->g command
//X-->x position
//Y-->y position
//Z-->z position
//E-->extruder
//F-->movement speed
//M(140)--> bed heating
//S-->extruder temperature in celsius
int commands[8];
int commandsindex = -1;
int gIndex = 0, xIndex = 1, yIndex = 2, zIndex = 3, eIndex = 4, fIndex = 5, mIndex = 6, sIndex = 7;
int commandCode = -1;
String command = "";

void interpret(String commandLine) {
  commandLine.trim();
  commandLine += ' ';
  Serial.println(commandLine);
  for (int i = 0; i < commandLine.length(); i++) {
    char c = commandLine.charAt(i);
    if (c != ' ') {
      command += c;
    } else if ( c == ' ') {
      //      for(int j = 0; j<command.length(); j++){
      //        char commandLetter = command.charAt(j);
      //        Serial.print(commandLetter);
      //      }
      //      Serial.println("\n---");
      //
      char commandHeader = command.charAt(0);
      switch (commandHeader) {
        case 'G':
          index = gIndex;
          break;
        case 'X':
          index = xIndex;
          break;
        case 'Y':
          index = yIndex;
          break;
        case 'Z':
          index = zIndex;
          break;
        case 'E':
          index = eIndex;
          break;
        case 'F':
          index = fIndex;
          break;
        case 'M':
          index = mIndex;
          break;
        case 'S':
          index = sIndex;
          break;
      }
      String tempCode = command.substring(1);
      commandCode = tempCode.toInt();
      Serial.print("Command:");
      Serial.print("Header=");
      Serial.print(commandHeader);
      Serial.print(", commandCode=");
      Serial.println(commandCode);
      command = "";
    }
  }
}
