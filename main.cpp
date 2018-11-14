
#include "moisture.h"
#include "relay.h"
#include "temp_humid.h"
#include "wiringPi.h"
#include <iostream>
#include <thread>
#include <chrono>

//Function prototypes
void temp();


using namespace std;
int main(){
	//wiringPiSetup();
	//pinMode(2, INPUT);

	//Thread to control the temperature
	thread temp_thread (temp);

	//Synch threads
	temp_thread.join();
	return 0;
}


void temp(){
	Temp_humid th;
	Relay relay;
	
	bool resp = false;
	int temp = 0; //Use first port on the relay for H
	int humid = 1; //Use second port on relay for humity;


	while(true){
		cout << "Before do while\n";
		do {
			resp = th.read_signal();
			this_thread::sleep_for(chrono::seconds(2));
		} while(resp == false);
		cout << "after do while\n";
		//If temp drops below 20C then turn on heater
		int cur_temp = th.get_temp();
		if(cur_temp < 20){
			cout << "Temp: " << cur_temp << "\nTurning on heat\n";
			relay.com_switch(temp, on);	
		}

		else{
			cout << "Temp: " << cur_temp << "\nTurning off head\n";
			relay.com_switch(temp, off);
		}
		this_thread::sleep_for(chrono::seconds(10));
			
	}
}
