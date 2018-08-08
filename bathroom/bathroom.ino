/*
 * bathroom - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include <avr/wdt.h>
#include <Wire.h>
#include "utils.h"
#include "rele.h"
#include "fan.h"

Fan fan;

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);

  wdt_enable(WDTO_2S);
}

void taskBathroomLights();
void taskThermostat();

/**
 * 
 */
void loop() {
	fan.task();
	taskBathroomLights();
	taskThermostat();

  wdt_reset();
}

void taskBathroomLights() {
  
}

void taskThermostat() {
  
}

