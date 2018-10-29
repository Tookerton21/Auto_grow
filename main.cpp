
#include "moisture.h"
#include "wiringPi.h"
#include <iostream>

using namespace std;
int main(){
	//wiringPiSetup();
	//pinMode(2, INPUT);
	Moisture m_sensor(1);

	cout << "PRINT STUFF" << endl;
	cout << "sensor num: " << m_sensor.get_num() << endl;
	cout << "Sensor Reading: " << m_sensor.get_read() << endl;
}
