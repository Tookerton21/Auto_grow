#include "relay.h"
#include <wiringPi.h>

//Port numbers for each of the switches using the wiringPi pin numbers
const int one = 1;
const int two = 2;
const int three = 3;
const int four = 4;

Relay::Relay(){
	sw[0] = one;
	sw[1] = two;
	sw[2] = three;
	sw[3] = four;

	wiringPiSetup();

	//INitiiale the pins for the board to correct pin and turn them all on off.
	for(int i=0; i<NUM; ++i){
		pinMode(sw[i], OUTPUT);
		digitalWrite(sw[i], 1);
	}
}

void Relay::com_switch(int n, int com){
	digitalWrite(sw[n], com);
}

