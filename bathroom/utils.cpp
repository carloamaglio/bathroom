/*
 * utils.cpp - 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include "utils.h"

Debounce::Debounce(DigitalInput *input, long delay) {
	this->input = input;
	this->delay = delay;
	lastTime = millis();
	lastInput = 0;
	state = 0;
}

void Debounce::task() {
	char in = input->value();
	if (in != lastInput) lastTime = millis();
	if ((millis() - lastTime) > delay) {
		state = in;
	}
	lastInput = in;
}



int Pulse::value() {
	Debounce::task();
	int v = Debounce::value();
	switch (state) {
		case 0:
			if (v) {
				state = 1;
				return 1;
			}
			break;
		case 1:
			if (!v) {
				state = 0;
				return -1;
			}
			break;
	}
	return 0;
}



int MultiFunctionBtn::value() {
	int p = Pulse::value();	// 0, 1, -1
	switch (state) {
		case 0:
			if (p==1) {
				state = 1;
				t->set(1000);
			}
			break;
		case 1:
			if (p==-1) {
				state = 0;
				return 1;
			} else if (t->value()) {
				state = 0;
				return 2;
			}
			break;
	}
	return 0;
}
