#include "relay.h"
#include <thread>
#include<chrono>
#include <iostream>

using namespace std;

int main() {
	Relay relay;

	//relay.com_switch(1,0);
	
	
	for(int i=0; i<4; ++i){
		cout << "switch: " << i << " ON" << endl;
		relay.com_switch(i,0);
		this_thread::sleep_for(chrono::seconds(1));
	}

	
	for(int i=3; i>=0; --i){
		cout << "switch: " << i << " OFF" << endl;
		relay.com_switch(i,1);
		this_thread::sleep_for(chrono::seconds(1));
	}
		}
