#include <Wire.h>
#include "hcrbot_gmr_n1.h"
#include "n1_configs.h" // Configurations

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

Mobilebase robot(BASEWIDTH, WHEELDIAMETER, MAXSPEED);
void initMobilebase(){
  // Mobilebase initialization
  robot.setPins(R_DIR, R_PWM, R_ENC_INT, R_ENC_OTHER, L_DIR, L_PWM, L_ENC_INT, L_ENC_OTHER);
  //robot.displayStats(&Serial);
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
       Serial.printrln("Command with C");
       robot.stop();
       robot.displayTicks(&Serial);
       break;
    default: Serial.println("Something else.");
       robot.stop();
  }
  cmdlen = 0;
  memset(cmdline,0,CMDBUFFER);
}

void leftTicks(){
  robot.lMotorTick();
}

void rightTicks(){
  robot.rMotorTick();
}


char i2c_cmdline[CMDBUFFER];
void wireReceive(int bytes){ 
  Serial.print("Received: ");
  Serial.println(bytes);
  if(Wire.available()){
    for(int i=0;i<bytes && i < CMDBUFFER;i++){
      i2c_cmdline[i] = Wire.read();
    }
  }
}
void wireRequest(){
  Serial.println("Serving the request...");
  switch(i2c_cmdline[0]){
    case 'A':
      Wire.write('A');
      break;
    case 'B':
      Wire.write('B');
      break;
    default:
      Wire.write('Z');     
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Slave program Started...");
  //initMobilebase();
  //attachInterrupt(1, leftTicks, RISING);
  //attachInterrupt(0, rightTicks, RISING);
  Wire.begin(N1_I2C_ADDR);
  Wire.onReceive(wireReceive);
  Wire.onRequest(wireRequest);
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



