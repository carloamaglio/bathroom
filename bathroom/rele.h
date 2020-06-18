/*
 * rele.h - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#ifndef RELE_H
#define RELE_H

#include <arduino.h>

class Rele {
  public:
    Rele();
    Rele(int addr, int state=0);
    void init(int addr, int state=0);
    void setValue(int value);
    int value();
  private:
    int addr;
    char _value;
};

#endif

