
const int NUM = 4;

enum status {
	on = 0,
	off = 1,
}
class Relay {
	private:
		int sw [NUM];

	public:
		Relay();
		void com_switch(int, int);
};
