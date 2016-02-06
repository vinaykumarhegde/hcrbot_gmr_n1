/*
	Motor Library;
	Author: Vinay

*/
#include "Arduino.h"
#include "hcrbot_gmr_n1.h"

Motor::Motor(){
  _dir = true; // Default: right wheel
}

Motor::Motor(char dir){
	_dir = (dir=='R' || dir == 'r')?true:false;
}

void Motor::setPins(uint8_t dir, uint8_t pwm){
  _dir_pin = dir;
  _pwm_pin = pwm;
}

void Motor::setDia(float dia){
  _cir = PI * dia;
}

void Motor::setMaxSpeed(uint16_t s){
  _max_speed = s;
}

void Motor::displayStats(HardwareSerial *s){
  s->println("Motor diagnostics:");  
}

Mobilebase::Mobilebase(uint8_t base, float dia, uint16_t maxSpeed){
  rMotor = new Motor('R');
  lMotor = new Motor('L');
  _base = base;
  rMotor->setDia(dia);
  lMotor->setDia(dia);
  rMotor->setMaxSpeed(maxSpeed);
  lMotor->setMaxSpeed(maxSpeed);
}

// Set Pins for Motors in Mobile Base
// Right Dir, Right PWM, Left Dir, Left PWM
Mobilebase::setPins(uint8_t r_dir,uint8_t r_pwm,uint8_t l_dir,uint8_t l_pwm){
  rMotor->setPins(r_dir,r_pwm);
  lMotor->setPins(l_dir,l_pwm);
}

Mobilebase::goForward(){
  
}

Mobilebase::goBackward(){
  
}

Mobilebase::turnInplaceLeft(){
  
}

Mobilebase::turnInplaceRight(){
  
}


