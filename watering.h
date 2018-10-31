#include "relay.h"
#include "moisture.h"
#include <ctime>
#include <cstdlib>

const int w_switch = 0; //Switch that constrols the watering pump

class Watering {
	private:
		Relay *relay;
		Moisture *level;
		int stop_time;
	public:
		Watering();
		void set_water_time(double);
		bool need_water();
		void give_water_timer();
		void give_water_no_timer(); 
};
