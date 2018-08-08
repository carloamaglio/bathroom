/*
 * fan.cpp - control a fan in the bathroom. 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include <arduino.h>
#include "fan.h"

Fan::Fan() {
  rele.setAddr(1);
}

void Fan::task() {
  rele.setState(!rele.getState());
}

