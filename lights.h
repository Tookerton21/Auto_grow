#include <string>
#include <ctime>
#include <chrono>
#include "relay.h"

enum grow_type {
	veg,
	bloom,
};

class Lights {
	private:
		bool on_veg;
		bool on_bloom;
		bool light;
		bool sleep;
		
		std::chrono::hours veg;
		std::chrono::hours flower;
		std::chrono::system_clock::time_point start;
		
		
		Relay *port;
		int port_num;
	public:
		Lights(int);
		void set_grow(grow_type);
		void turn_light_on();
		void turn_light_off();

};
