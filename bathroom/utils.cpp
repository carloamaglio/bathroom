/*
 * utils.cpp - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include "utils.h"

void timerSet(timer* t, unsigned long interval) {
  t->interval = interval;
  t->start = millis();
}

int timerExpired(timer* t) {
  return (millis() - t->start) >= t->interval;
}

