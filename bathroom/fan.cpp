/*
 * fan.cpp - control a fan in the bathroom 
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 * Released into the public domain
 */

#include <arduino.h>
#include "utils.h"
#include "rele.h"
#include "fan.h"

#define PERIOD 10*60*1000L
#define	BTNINP			A4
#define OUT				6
static DigitalInput btnInput(BTNINP, 0);
static MultiFunctionBtn btn(&btnInput);
static Rele rele(OUT);
static int umidity;
static int btstate;
static int umstate;
static Delay t;

void fanSetup() {
	btstate = -1;
	umstate = 0;
	rele.setValue(0);
}

void fanLoop() {
	//return;
	if (btstate >= 0) {
		int v = btn.value();
		if (v==1) {
			t.set(PERIOD);
			btstate = !btstate;
		} else if (v==2) {
			t.set(10*PERIOD);
			btstate = !btstate;
		} else if (btstate==1 && t.value()) {
			btstate = 0;
		}

		if (umidity > 70) {
			umstate = 1;
		} else if (umidity < 65) {
			umstate = 0;
		}

		rele.setValue(btstate || umstate);
	} else {
		if (btstate == -1) {
			rele.setValue(1);
			t.set(500L);
			btstate = -2;
		} else if (btstate==-2 && t.value()) {
			rele.setValue(0);
			t.set(500L);
			btstate = -3;
		} else if (btstate==-3 && t.value()) {
			btstate = 0;
		}
	}
}

