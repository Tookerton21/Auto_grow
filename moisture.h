//Class to controll the moisture sensors


//Enum for the moisture level
enum level {
	wet,
	dry,
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

