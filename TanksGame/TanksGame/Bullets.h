ref class Bullets{
private:
	int x, y;

public:
	Bullets(int, int);

	void travel(int destination_x, int destination_y);
	int get_x();
	int get_y();

};