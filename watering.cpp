#include "watering.h"
#include <thread>
#include<chrono>

Watering::Watering(){
	relay = new Relay();
	level = new Moisture(0);
	stop_time = 60; //Default is 60 seconds
}

//Check the level of the water in the sensors
//Return appropriate reading for whether it needs
//H20 or not. 
bool Watering::need_water(){
	if(level->get_read() == dry)
		return true;
	else
		return false;
}

//Set the amount of time to water in sec
void Watering::set_water_time(double time){
	stop_time = time;
}
//Turn on the water pump to start giving water
void Watering::give_water_timer(){
	relay->com_switch(w_switch, on);
	clock_t start_time = clock();//Start clock
	
	while((clock - start_time) / CLOCKS_PER_SEC < stop_time){
		//Put thread to sleep while watering
		this_thread::sleep_for(chrono::seconds(1));
	}

	relay->com_switch(w_switch, off); //Turn off the watering
}

//Turn on water pump without timer
void Watering::give_water_no_timer(){
	relay->com_switch(w_switch, on);

	while(level->get_read() == dry){
		//Put thread to sleep while watering
		this_thread::sleep_for(chrono::seconds(1));
	}

	relay->com_switch(w_switch, off);
}

