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
#include "light.h"
#include "lightshower.h"


/**
 * 
 */
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);

  fanSetup();
  lightSetup();
  lightShowerSetup();

  p("setup executed\n");
  wdt_enable(WDTO_2S);
}

/**
 * 
 */
void loop() {
	fanLoop();
	lightLoop();
	lightShowerLoop();

	wdt_reset();
}


