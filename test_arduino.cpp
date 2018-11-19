/*
 * Keep in mind that when you are sending Strings to the arduino via the serial library
 * That it is refering to char arrays and not the actual strings
*/

#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>

using namespace std;
int main(){
	char pi[] = "/dev/ttyACM0";

	int descrip = serialOpen(pi, 9600);
	cout << "out: " << descrip << endl;
	delay(7000);
//	for(int i = 0; i<4; ++i){
		char t[]="true";
		serialPuts(descrip, t);
		delay(3000);
		char port[] = "2";
		serialPuts(descrip, port);
		delay(3000);
		char sig[] = "high";
		serialPuts(descrip, sig);
		
//	}

	//serialClose(descrip);
}
