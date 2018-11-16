#include "lights.h"
Lights::Lights(int p){
	on_veg = false;
	on_bloom = false;
	light = false;
	sleep = false;

	veg = std::chrono::hours(18);
	flower = std::chrono::hours(12);
	
	start = std::chrono::system_clock::now();
	
	port_num = p;
	port = new(p);
}

void Lights::set_grow(grow_type type){
	if(type == veg)
		on_veg = true;

	if(type == bloom)
		on_bloom = true;
}

void Lights::turn_light_on(){
	start = std::chrono::system_clock::now();//start the timer
	port(port_num, on);//turn lights on
	light = true;//set light on flag to true;
	sleep = false;//and sleep to true;
}

void turn_light_off{
	start = std::chrono::system_clock::now();//start the timer
	port(port_num, off);//turn off lights
	light = false;//Set light flag to fals3
	sleep = true;//and sleep flag to true
}
