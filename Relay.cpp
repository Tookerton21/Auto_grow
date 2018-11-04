#include "relay.h"
#include <wiringPi.h>

//Port numbers for each of the switches using the wiringPi pin numbers
const int one = 0;
const int two = 1;
const int three = 2;
const int four = 3;

Relay::Relay(){
	sw[one] = one;
	sw[two] = two;
	sw[three] = three;
	sw[four] = four;

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

