/*
 * lightshower.cpp - control shower lights in the bathroom. 
 *	
 *
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 *	Released into the public domain
 */

#include <arduino.h>
#include "utils.h"
#include "rele.h"
#include "lightshower.h"

#define BTNINP				A2
#define OUT					4
#define NICHEOUT			5
#define	PIRINP				A3	// PIR sensor input
static DigitalInput			pirInput(PIRINP, 1);
#define PIROFFPERIOD		(2*60L*1000L)

#define AUTOOFFPERIOD		(2*3600L*1000L)
static DigitalInput btnInput(BTNINP, 0);
static MultiFunctionBtn btn(&btnInput);

static Rele rele(OUT);
static Rele nicheRele(NICHEOUT);

void lightShowerSetup() {
	rele.setValue(0);
	nicheRele.setValue(0);
}

void lightShowerLoop(int cmd) {
	static int state = -1;
	static Delay autoOff;

	static int pirState = 0;
	static Delay pirTimer;

	if (cmd==1) {
		state = 0;
		pirState = 0;
	}

	//return;
	if (state >= 0) {
		int v;

		/* button:
		 * 	with short push/release cycle through the sequence 00->10->11->01->00
		 *	with long push/release switch ON/OFF both the first and second lights
		 */
		v = btn.value();
		if (v) autoOff.set(AUTOOFFPERIOD);	// retrig the auto Off timer
		if (v==1) {
			if (state==0) state = 2;
			else if (state==2) state = 3;
			else if (state==3) state = 1;
			else if (state==1) state = 0;
		} else if (v==2) {
			if (state==0) state = 1|2;
			else state = 0;
		}

		// switch off everithing if auto Off timer is expired
		if (autoOff.value()) {
			state = 0;
		}


		if (state) {	// if light switched on by button disable pir sensor
			pirState = 0;
		} else if (pirInput.value()) {
			if (pirState==0) p("PIR ON\n");
			p("PIR=1\n");
			pirState = 1;
			pirTimer.set(PIROFFPERIOD);
		} else {
			p("PIR=0\n");
			if (pirState && pirTimer.value()) {
				pirState = 0;
			}
		}

		rele.setValue(state & 1);
		nicheRele.setValue((state & 2) || pirState);
	} else {
		if (state == -1) {
			rele.setValue(1);
			nicheRele.setValue(0);
			autoOff.set(1010L);
			state = -2;
		} else if (state==-2 && autoOff.value()) {
			rele.setValue(1);
			nicheRele.setValue(1);
			autoOff.set(1010L);
			state = -3;
		} else if (state==-3 && autoOff.value()) {
			rele.setValue(0);
			nicheRele.setValue(1);
			autoOff.set(1010L);
			state = -4;
		} else if (state==-4 && autoOff.value()) {
			rele.setValue(0);
			nicheRele.setValue(0);
			autoOff.set(1010L);
			state = -5;
		} else if (state==-5 && autoOff.value()) {
			state = 0;
		}
	}
}


void lightShowerSwitchOff() {
	lightShowerLoop(1);
}
