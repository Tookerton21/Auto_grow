//Class to controll the moisture sensors


//Enum for the moisture level
enum level {
	wet = 1,
	dry = 0,
};

class Moisture {
	private:
		level reading;
		int num;

	public:
		Moisture(int);  //Constructor
		level get_read();
		int get_num();
};

