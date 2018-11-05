#include "temp_humid.h"
#include "iostream"

using namespace std;

int main(){
	Temp_humid th;

	bool valid = th.read_signal();

	if(valid == true){
		int temp = th.get_temp();
		int humid = th.get_humid();

		cout << "humidity: " << humid << endl;
		cout << "temp: " << temp << " C\n";
	}	
	else
		cout << "Could not get valid reading\n";
}
