#include "relay.h"
#include "moisture.h"
#include <ctime>
#include <cstdlib>

const w_switch = 0; //Switch that constrols the watering pump

class Watering {
	private:
		Relay *relay;
		Moisture *level;
	public:
		Watering();
		bool need_water();
};