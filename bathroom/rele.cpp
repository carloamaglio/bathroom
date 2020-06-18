/*
 * rele.cpp - control a single rele. It can be local or (to be developed) remoted to an I2C expansion device
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include <arduino.h>
#include "rele.h"


Rele::Rele() {
}

Rele::Rele(int addr, int value=0) {
  init(addr, value);
}

void Rele::init(int addr, int value=0) {
  this->addr = addr;
  pinMode(addr, OUTPUT);
  setValue(value);
}

void Rele::setValue(int value) {
  digitalWrite(addr, value==0);
  _value = value;
}

int Rele::value() {
  return _value;
}

