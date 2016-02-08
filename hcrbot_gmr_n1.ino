#include <Wire.h>
#include "hcrbot_gmr_n1.h"

// Configurations
#include "n1_configs.h"

char cmdline[CMDBUFFER]; // 10 bytes max for commands.
unsigned int cmdlen = 0; // Length of received command
//bool cmd = false; // Flag to say command is present or not.

/*
  unsigned char n[] = {0xFF,0xFF,0x00,0x01};
  int i,j;






  
  Serial.println(n[0],BIN);Serial.println(n[1],BIN);
  Serial.println(n[2],BIN);Serial.println(n[3],BIN);
  i = int(n[1] + (n[0] << 8));
  Serial.println(i,DEC);
  j = n[3] + (n[2] << 8);
  Serial.println(j,BIN);
*/


Motor mRight('R'),mLeft('L');


void initMotors(){
  mRight.setPins(R_DIR,R_PWM);
  mRight.setDia(136);
  mRight.setMaxSpeed(MAXSPEED);
  mLeft.setPins(L_DIR,L_PWM);
  mLeft.setDia(136);
  mLeft.setMaxSpeed(MAXSPEED);
  mLeft.displayStats(&Serial);
}

Mobilebase robot(BASEWIDTH, WHEELDIAMETER, MAXSPEED);
void initMobilebase(){
  // Mobilebase initialization
  robot.setPins(R_DIR, R_PWM, L_DIR, L_PWM);
  //robot.displayStats(&Serial);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Program Started...");
  //initMotors();
  initMobilebase();
}

void processCmd(){
  Serial.println("Found command");
  Serial.print("Entered: "); Serial.print(cmdlen);
  Serial.print('\n');
  switch(cmdline[0]){
    case 'A':
    case 'a': Serial.println("Command with A");
       robot.goForward(128,128);
       break;
    case 'B':
    case 'b': Serial.println("Command with B");
       robot.goBackward(128,128);
    break;
    case 'C':
    case 'c':
       Serial.println("Command with C");
       robot.stop();
       break;
    default: Serial.println("Something else.");
       robot.stop();
  }
  cmdlen = 0;
  memset(cmdline,0,CMDBUFFER);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() && cmdlen < CMDBUFFER){
    char c = Serial.read();
    if(c != '\n'){
      cmdline[cmdlen++] = c;
    } else {
      processCmd();
    }
  }
}



