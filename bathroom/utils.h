/*
 * utils.h - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#ifndef UTILS_H
#define UTILS_H

#include <arduino.h>
#include <stdio.h>

typedef struct timer {
  unsigned long start;
  unsigned long interval;
} timer;

extern void timerSet(timer* t, unsigned long interval);
extern int timerExpired(timer* t);

#ifdef DEBUG
#define p(S)	Serial.print(S)
#define pln(S)	Serial.println(S)
#else
#define p(S)
#define pln(S)
#endif

#endif
