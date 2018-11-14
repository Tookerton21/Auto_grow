
#include "watering.h"

#include "temp_humid.h"
#include "wiringPi.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

//Function prototypes
void temp();
void water();

using namespace std;

//Global Variables
mutex in_use;
bool in_use_temp = false;

int main(){
	//wiringPiSetup();
	//pinMode(2, INPUT);
//	bool in_use_temp = false;
	//Thread to control the temperature
	thread temp_thread (temp);
	thread water_thread(water);
	
	//Synch threads
	temp_thread.join();
	water_thread.join();
	
	return 0;
}

//Check the moisture level of he soil every 4 hrs, if moisture is low then water with the timer of 5 min. 
void water() {
	Watering w;
	double timer = 5;
	w.set_water_time(timer);
	
	bool res;

	//Inf while loop to check watering status
	while(true){
		res = w.need_water();

		if(res == true){
			w.give_water_timer();
		}
		this_thread::sleep_for(chrono::hours(4));
	}	
}

//Prefered temp is 20-30 C
void temp(){
	Temp_humid th;
	Relay relay;
	
	bool resp = false;
	int heater = 0; //Use first port on the relay for H
	int air_cond = 1; //air cond is on pi port 1;
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

		//Below 20 C so turn on the heater
		if(cur_temp < 20){
			cout << "Temp: " << cur_temp << "\nTurning on heat\n";
			
			//Lock the shared variable
			in_use.lock();
				//If in use not being used turn to true and run on the heater.
				if(in_use_temp == false){
					in_use_temp = true;
					relay.com_switch(heater, on);
				}
			in_use.unlock();
		}
		
		//In the perfect range, and turn either of them off
		else if( cur_temp >= 20 && cur_temp < 30){
			relay.com_switch(heater, off);
			relay.com_switch(air_cond, off);

			//Set the insuse for flag to false
			in_use.lock();
				in_use_temp = false;
			in_use.unlock();
		}
		else{
			//Check flag and turn on air cond
			in_use.lock();
				if(in_use_temp == false){
					in_use_temp = true;
					relay.com_switch(air_cond, on);
				}
			in_use.unlock();
		}
		
		//Put the thread to sleep before cheking again
		this_thread::sleep_for(chrono::seconds(60*5));
			
	}
}
