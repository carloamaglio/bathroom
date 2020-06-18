/*
 * light.cpp - control main lights in the bathroom. 
 *	There're two indipendent main lights. There is a ON/OFF switch near the door and a button near the mirror.
 *
 *  Carlo Amaglio, Via Emigli 10 - 25081 Bedizzole (Italy)
 * 
 *	Released into the public domain
 */

#include <arduino.h>
#include "utils.h"
#include "rele.h"
#include "light.h"

#define	SWITCHINP		A0	// main lights door ON/OFF switch
#define	BTNINP			A1	// main lights mirror button
#define LIGHT1OUT		2	// main light 1 output
#define LIGHT2OUT		3	// main light 2 output
#define AUTOOFFPERIOD	(2*3600L*1000L)
static DigitalInput doorBtnInput(SWITCHINP, 0);
static MultiFunctionBtn doorBtn(&doorBtnInput);
static DigitalInput mirrorBtnInput(BTNINP, 0);
static MultiFunctionBtn mirrorBtn(&mirrorBtnInput);

static Rele light1Rele(LIGHT1OUT);
static Rele light2Rele(LIGHT2OUT);

void lightSetup() {
	light1Rele.setValue(0);
	light2Rele.setValue(0);
}

void lightLoop() {
	static int state = -1;
	static Delay autoOff;
	int v;

	//return;

	if (state >= 0) {
		/* Door button:
		 * 	with short push/release switch ON/OFF only the first light
		 *	with long push/release switch ON/OFF both the first and second lights
		 */
		v = doorBtn.value();
		if (v) autoOff.set(AUTOOFFPERIOD);	// retrig the auto Off timer
		if (v==1) {
			if (state==0) state = 1;
			else state = 0;
		} else if (v==2) {
			if (state==0) state = 1|2;
			else state = 0;
		}

		/* Mirror button:
		 * 	with short push/release cycle through the sequence 01->11->10->00->10
		 *	with long push/release switch ON/OFF both the first and second lights
		 */
		v = mirrorBtn.value();
		if (v) autoOff.set(AUTOOFFPERIOD);	// retrig the auto Off timer
		if (v==1) {
			if (state==0) state = 2;
			else if (state==2) state = 0;
			else if (state==1) state = 3;
			else if (state==3) state = 2;
		} else if (v==2) {
			if (state==0) state = 1|2;
			else state = 0;
		}

		// switch off everithing if auto Off timer is expired
		if (autoOff.value()) {
			state = 0;
		}
		light1Rele.setValue(state & 1);
		light2Rele.setValue(state & 2);
	} else {
		if (state == -1) {
			light1Rele.setValue(1);
			light2Rele.setValue(0);
			autoOff.set(1000L);
			state = -2;
		} else if (state==-2 && autoOff.value()) {
			light1Rele.setValue(1);
			light2Rele.setValue(1);
			autoOff.set(1000L);
			state = -3;
		} else if (state==-3 && autoOff.value()) {
			light1Rele.setValue(0);
			light2Rele.setValue(1);
			autoOff.set(1000L);
			state = -4;
		} else if (state==-4 && autoOff.value()) {
			light1Rele.setValue(0);
			light2Rele.setValue(0);
			autoOff.set(1000L);
			state = -5;
		} else if (state==-5 && autoOff.value()) {
			state = 0;
		}
	}
}

