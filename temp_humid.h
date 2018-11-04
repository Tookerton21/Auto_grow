#include <wiringPi.h>
#include <vector>

const int PIN = 4; //Pin for the temp/humid sensor on the pi

class Temp_humid {
	private:
		int temp;
		int humid;
		void send_signal();
	 	int convert_binary(unsigned int[]);	
		//void read_signal();
	public:
		Temp_humid();
		void get_reading();
		void read_signal();
};
