#include <wiringPi.h>
#include <chrono>
#include <ctime>
#include "temp_humid.h"
#include <iostream>
#include <string>
#include <math.h> 

//const int PIN = 3;//PIN FOR THE SENSOR ON THE PI

Temp_humid::Temp_humid(){
	wiringPiSetup();

	temp = 0;
	humid = 0;
	for(int i=0; i <SIZE; ++i)
		byte[i] = 0;
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

bool Temp_humid::read_signal(){
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
			return false;;

		--loop;
	}
	loop = 10000; //reset max to check for the high signal

	while(digitalRead(PIN) == HIGH){
		if(loop < 0)
			return false;;

		--loop;
	}

	unsigned time_e;
	//Response is 40 bits so we will have 40 cycles
		for (int i=0; i<40; ++i){
			time_e = micros();
			//Low response

			while(digitalRead(PIN) == LOW){
			}
			loop = 1000;

			time_e = micros();
			while(digitalRead(PIN) == HIGH){
				if (loop == 0)
					break;
				--loop;
			}
		
			bit[i] = micros() - time_e;

		}

	for(int i = 0; i <40; i += 8){
		unsigned int *start = bit+i;
		byte[i/8] = convert_binary(start);
	}
	
	return checksum(byte);

}

int Temp_humid::convert_binary(unsigned int byte[]){
	int sum = 0;

	for(int i=0; i<8; ++i){
		if(byte[i] > 30){
			sum += pow(2.0, (7.0-(double)i));
		}	
	}

	return sum;
}

bool Temp_humid::checksum(int arr[]){
	int sum = 0;

	for(int i=0; i<SIZE-1; ++i)
		sum += arr[i];

	if(sum == arr[SIZE-1]){
		humid = arr[0];
		temp = arr[2];
		return true;
	}
	return false;
}

int Temp_humid::get_temp(){
	return temp;
}

int Temp_humid::get_humid(){
	return humid;
}
