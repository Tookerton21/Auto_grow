#include "watering.cpp"
#include <iostream>

using namespace std;

int main() {
	//Variable declaration
	Watering water;
	char input = 'c';

	//While loop that checks the water status, if water is needed
	//Then proceed to water until sensor says that it has been saturated
	//enough.
	while(input != 'q'){
		if(water.need_water() == true){
			water.give_water_no_timer();
		}
	}


}