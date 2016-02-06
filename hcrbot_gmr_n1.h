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
	bool _dir; // True if clockwise motor rotation is forward motion for robot.
  float _cir; // Circumference
	uint16_t _ppr; // Encoder pulses per revolution.
  uint8_t _dir_pin; // Enable/Direction pin
  uint8_t _pwm_pin; // PWM pin.
  uint16_t _max_speed; // Max speed in mmps
  
public:	
	unsigned int ticks;
	Motor();
  Motor(char);
  void setPins(uint8_t,uint8_t);
  void setDia(float);
  void setMaxSpeed(uint16_t);
  void displayStats(HardwareSerial*);
};

class Mobilebase{
private:
  Motor rMotor;
  Motor lMotor;
  uint8_t _base; // Baseline distance in mm

public:
  Mobilebase(uint8_t,float,uint16_t);
  setPins(,uint8_t,uint8_t,uint8_t,uint8_t);
};

#endif
