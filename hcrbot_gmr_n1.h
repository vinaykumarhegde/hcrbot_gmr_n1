/*
Include file.
Author: Vinaykumar Hegde

*/

#ifndef hcrbot_gmr_n1_h
#define hcrbot_gmr_n1_h

typedef unsigned char uchar;
typedef unsigned int uint;

class Motor{
private:
  float _cir; // Circumference
	uint16_t _ppr; // Encoder pulses per revolution.
  uint8_t _dir_pin; // Enable/Direction pin
  uint8_t _pwm_pin; // PWM pin.
  uint8_t _enc_int; // Encoder interrupt pin
  uint8_t _enc_other; // Encoder other pin
  uint16_t _max_speed; // Max speed in mmps
  bool _dir; // True if clockwise motor rotation is forward motion for robot.
  
  
public:	
	unsigned long ticks;
	Motor();
  void setPins(uint8_t,uint8_t,uint8_t,uint8_t);
  void setDia(float);
  void setMaxSpeed(uint16_t);
  void rotateCW(uint8_t);
  void rotateACW(uint8_t);
  void stop(void);
  void displayStats(HardwareSerial*);
  void encoderTick(void);
  bool getDir(void);
};

class Mobilebase{
public:
  Motor* rMotor;
  Motor* lMotor;
  uint8_t _base; // Baseline distance in mm

//public:
  Mobilebase(uint16_t,float,uint16_t);
  void setPins(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
  void goForward(uint8_t,uint8_t);
  void goBackward(uint8_t,uint8_t);
  void turnInplaceLeft(uint8_t,uint8_t);
  void turnInplaceRight(uint8_t,uint8_t);
  void stop(void);
  void displayStats(HardwareSerial*);
  void displayTicks(HardwareSerial*);
  void rMotorTick();
  void lMotorTick();
};

#endif
