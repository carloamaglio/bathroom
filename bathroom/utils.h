/*
 * utils.h - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#ifndef UTILS_H
#define UTILS_H

#include <arduino.h>
//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif

class Delay {
  public:
	Delay() {};
	void set(unsigned long interval) {
		this->interval = interval;
		this->start = millis();
	};
	// 1=elapsed
	int value() {
		return (millis() - start) >= interval;
	};
  private:
	unsigned long start;
	unsigned long interval;
};


class DigitalInput {
  public:
    DigitalInput(int addr, char trueValue=1) {
		this->addr = addr;
		this->trueValue = (trueValue!=0);
		if (addr>=A0) {
			pinMode(addr,  INPUT_PULLUP);
		} else {
			pinMode(addr, INPUT);
			digitalWrite(addr, 1);
		}
	}
    char value() { return (digitalRead(addr)!=0) == trueValue; }
  private:
	int addr;
	char trueValue;
};


class Debounce {
  public:
    Debounce(DigitalInput *input, long delay=50);
    void task();
    char value() { return state; }
  private:
	DigitalInput *input;
	long delay;
	long lastTime;
	char lastInput;
    char state;
};


class Pulse : Debounce {
	public:
		Pulse(DigitalInput *input, long delay) : Debounce(input, delay) {}
		Pulse(DigitalInput *input) : Debounce(input) {}
		int value();
	private:
		int state;
};


class MultiFunctionBtn : Pulse {
	public:
		MultiFunctionBtn(DigitalInput *input) : Pulse(input) {}
		int value();	// 0=no edge event, 1=rising edge, -1=falling edge
	private:
		int state;
		Delay t[1];
};


#ifdef DEBUG
#define p(S)	Serial.print(S)
#define pln(S)	Serial.println(S)
#else
#define p(S)
#define pln(S)
#endif

#endif
