#include <wiringPi.h>
#include <vector>

const int PIN = 4; //Pin for the temp/humid sensor on the pi
const int SIZE = 5;

class Temp_humid {
	private:
		int temp;
		int humid;
		int byte[SIZE];
		void send_signal();
	 	int convert_binary(unsigned int[]);
		bool checksum(int[]);	
		//void read_signal();
	public:
		Temp_humid();
		void get_reading();
		bool read_signal();
		int get_temp();
		int get_humid();
};
