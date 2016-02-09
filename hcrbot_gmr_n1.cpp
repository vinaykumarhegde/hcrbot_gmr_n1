/*
	Motor Library;
	Author: Vinay

*/
#include "Arduino.h"
#include "hcrbot_gmr_n1.h"

Motor::Motor(){
  // Constructor
  ticks = 0;
}

void Motor::setPins(uint8_t dir, uint8_t pwm, uint8_t enc_int, uint8_t enc_other){
  _dir_pin = dir;
  _pwm_pin = pwm;
  _enc_int = enc_int;
  _enc_other = enc_other;
}

void Motor::setDia(float dia){
  _cir = PI * dia;
}

void Motor::setMaxSpeed(uint16_t s){
  _max_speed = s;
}

void Motor::displayStats(HardwareSerial *s){
  s->println("\tMotor diagnostics:");
  s->print("\tPWM Pin: ");
  s->println(_pwm_pin);
  s->print("\tDIR Pin: ");
  s->println(_dir_pin);
  s->print("\tMaxSpeed: ");
  s->println(_max_speed);
  s->print("\tCircumference: ");
  s->println(_cir);
}

void Motor::rotateCW(uint8_t s){
  analogWrite(_pwm_pin,s); // Set the PWM
  digitalWrite(_dir_pin,LOW); // Enable Cloclwise direction
}

void Motor::rotateACW(uint8_t s){
  analogWrite(_pwm_pin,s); // Set the PWM
  digitalWrite(_dir_pin,HIGH); // Enable Cloclwise direction
}

void Motor::stop(void){
  digitalWrite(_pwm_pin,LOW);  
  digitalWrite(_dir_pin,0);  
}

void Motor::encoderTick(){
  uint8_t val = digitalRead(_enc_other);
  _dir = (val)?true:false;
  ticks++;
}

bool Motor::getDir(){
  return _dir;
}

Mobilebase::Mobilebase(uint16_t base, float dia, uint16_t maxSpeed){
  rMotor = new Motor;
  lMotor = new Motor;
  _base = base;
  rMotor->setDia(dia);
  lMotor->setDia(dia);
  rMotor->setMaxSpeed(maxSpeed);
  lMotor->setMaxSpeed(maxSpeed);
}

// Set Pins for Motors in Mobile Base
// Right Dir, Right PWM, Left Dir, Left PWM
void Mobilebase::setPins(uint8_t r_dir,uint8_t r_pwm,uint8_t r_enc_int,uint8_t r_enc_other,uint8_t l_dir,uint8_t l_pwm,uint8_t l_enc_int,uint8_t l_enc_other){
  rMotor->setPins(r_dir,r_pwm,r_enc_int,r_enc_other);
  lMotor->setPins(l_dir,l_pwm,l_enc_int,l_enc_other);
}

void Mobilebase::goForward(uint8_t rightSpeed, uint8_t leftSpeed){
  rMotor->rotateCW(rightSpeed);
  lMotor->rotateACW(leftSpeed);
}

void Mobilebase::goBackward(uint8_t rightSpeed, uint8_t leftSpeed){
  rMotor->rotateACW(rightSpeed);
  lMotor->rotateCW(leftSpeed);
  
}

void Mobilebase::turnInplaceLeft(uint8_t rightSpeed, uint8_t leftSpeed){
  rMotor->rotateCW(rightSpeed);
  lMotor->rotateCW(leftSpeed);  
}

void Mobilebase::turnInplaceRight(uint8_t rightSpeed, uint8_t leftSpeed){
  rMotor->rotateACW(rightSpeed);
  lMotor->rotateACW(leftSpeed);
}

void Mobilebase::stop(void){
  rMotor->stop();
  lMotor->stop();
}

void Mobilebase::displayStats(HardwareSerial *s){
  s->println("Motor diagnostics:");
  s->println("Right motor:");
  rMotor->displayStats(s);
  s->println("Left motor:");
  lMotor->displayStats(s);
}

void Mobilebase::displayTicks(HardwareSerial *s){
  s->println("Right Motor Ticks:");
  s->print("\t Count: ");
  s->println(rMotor->ticks);
  s->print("\t Direction: ");
  rMotor->getDir()?s->println("Forward"):s->println("Backward");
  s->println("Lefht Motor Ticks:");
  s->print("\t Count: ");
  s->println(lMotor->ticks);
  s->print("\t Direction: ");
  lMotor->getDir()?s->println("Forward"):s->println("Backward");
  rMotor->ticks = 0;
  lMotor->ticks = 0;
}

void Mobilebase::rMotorTick(){
  rMotor->encoderTick();
}

void Mobilebase::lMotorTick(){
  lMotor->encoderTick();
}

