 
#include "moisture.h"
#include <wiringPi.h>
#include <iostream>

const int SENSOR = 0;//WiringPi Pin num, pin 3 on board

Moisture::Moisture(int n): reading(dry), num(n) {
	wiringPiSetup();
	pinMode(SENSOR, INPUT);
};

//Will return a 1 if there is NO moisture 
level Moisture::get_read() { 
	int res = digitalRead(SENSOR); //Save the reading to the digital Read Sensor	
	if (res == 1)
		reading = dry;
	else
		reading = wet;

	return reading;
}
int Moisture::get_num() { 
	return num;
}
