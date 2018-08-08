/*
 * fan.h - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#ifndef FAN_H
#define FAN_H

#include <arduino.h>
#include "rele.h"

class Fan {
  public:
    Fan();
    void task();
  private:
    Rele rele;
};

#endif

