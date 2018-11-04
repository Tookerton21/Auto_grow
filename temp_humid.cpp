#include <wiringPi.h>
#include <chrono>
#include <ctime>
#include "temp_humid.h"
#include <iostream>
#include <string>

//const int PIN = 3;//PIN FOR THE SENSOR ON THE PI

Temp_humid::Temp_humid(){
	wiringPiSetup();

	temp = 0;
	humid = 0;
}


/*
 * pull down the bus for more than 
 * 18ms
 *  in order to give DHT time to understand 
 *  it and then pull it up for 
 *  40uS
 */
void Temp_humid::send_signal(){
	pinMode(PIN, OUTPUT);	//Set pin to output
	
	//Pull the pin down for 18 mili sececonds
	digitalWrite(PIN, LOW);
	delay(18);

	//Pull the pin up for 40 microSeconds
	digitalWrite(PIN, HIGH);
	delayMicroseconds(43);
	
}

void Temp_humid::read_signal(){
	using namespace std::chrono;

	//Variable declaration
	microseconds micro(1000000);
	duration<double> max_time = duration_cast<duration<double>>(90*micro); //Max time wating for a signal change

	unsigned int cur_state = digitalRead(PIN); //Get the current state of the  sensor
	unsigned int new_state;

	bool on_low = true;//Start of the high time

	high_resolution_clock::time_point start_t;
	high_resolution_clock::time_point stop_t;//stop of the high time
	high_resolution_clock::time_point low_t = high_resolution_clock::now();

	std::vector<duration<double>> time_vec;

	//send_signal();

	//Wait for response
	int loop = 10000;
	bool failed = false;
	unsigned int bit[40];

	send_signal();
	while(digitalRead(PIN)==LOW){
		if(loop < 0)
			failed == true;

		--loop;
	}
	loop = 10000; //reset max to check for the high signal

	while(digitalRead(PIN) == HIGH){
		if(loop < 0)
			failed == true;

		--loop;
	}

	unsigned time_e;
	//Response is 40 bits so we will have 40 cycles
	if(failed != true)
		for (int i=0; i<40; ++i){
			time_e = micros();
			//Low response

			while(digitalRead(PIN) == LOW){
			//std::cout << "time elapsed in low: " << micros()-time_e << std::endl;
			}
	//		std::cout << "end low; time: " << micros() - time_e << std::endl;
			loop = 1000;

			time_e = micros();
			while(digitalRead(PIN) == HIGH){
				if (loop == 0)
					break;
				--loop;
			}
			
			bit[i] = micros() - time_e;
			//std::cout << "end high; time: " << micros()-time_e << std::endl;

		}
	else{
		std::cout << "signal failed\n";
	}

	for(int i = 0; i <40; i += 8){
		//std::cout << "bit[" << i << "]: " << bit[i] << std::endl;
		unsigned int *start = bit+i;
		std::cout << "BYTE: " << convert_binary(start) << std::endl;
	}
}

int Temp_humid::convert_binary(unsigned int byte[]){
	int sum = 0;
	for(int i=0; i<8; ++i){
		if(byte[i] < 30)
			sum += 2^(7-i);	
	}

	return sum;
}

void Temp_humid::get_reading(){
	uint8_t laststate = HIGH;
	uint8_t counter = 0;

	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);
	delay(18);

	pinMode(PIN, INPUT);

	for (int i=0; i < 85; ++i){
		counter = 0;
		while(digitalRead(PIN) == laststate){
			++counter;
			delayMicroseconds(1);
			if (counter == 255)
				break;
			
		}
		laststate = digitalRead(PIN);
		if(counter == 255)
			break;
		

		//ignore first 3 transitions
		
	}
}

