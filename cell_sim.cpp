#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Cell {
protected:
	int alive; //0 = dead cell, 1 = alive
	char type; //type of cell: O = normal cell, X = cancer cell
public:
	//Constructors
	Cell();
	Cell(int a, char b) :
		alive(a), type(b) {}

	//getter functions
	int get_alive() {
		return alive;
	}
	char get_type() {
		return type;
	}
	//set functions
	void set_alive(int a) {
		alive = a;
	}
	void set_type(char a) {
		type = a;
	}

	//gets number of neighbours for each cell and checks if it needs to die or be born
	virtual void neighbours(int d) {

		if (type == ' ') {
			if (d == 3) {
				alive = 1;
				type = 'O';
			}
		}

		else {
			if (d >= 5) {
				alive = 0;
				type = ' ';
			}

			else if (d <= 2) {
				alive = 0;
				type = ' ';
			}
		}
	}

	virtual ~Cell() {}; //destructor
};

Cell::Cell() {
	alive = 0;
	type = ' ';
}

class Cancer : public Cell {
public:
	Cancer(int a, char b) :
		Cell(a, b) {};

	void neighbours(int d) {
		if (type == ' ') {
			if (d == 3) {
				alive = 1;
				type = 'X';
			}
		}
		else {	
			if (d >= 6) {
				alive = 0;
				type = ' ';
			}

			else if (d <= 2) {
				alive = 0;
				type = ' ';
			}
		}
	}
	~Cancer(){};
};

class Board {
private:
	vector<vector<Cell*> > b;
	int time;
public:
	Board(); //constructor	

	void seed_cells(int select, double p);
	int get_time();
	int get_num_cells();
	void display();
	void next_state();
	int neighbouring(int x, int y);
	~Board() {}; //destructor
};

Board::Board() {
	time = -1;
}

int main() {
	int select = 0;
	int c;
	c = 0;
	double p = 0;

	Board board;
	string trash;

	system("cls");
	cout << "Welcome to the cell simulator" << endl;
	cout << endl;
	cout << "Would you like to simulate normal cells or cancer cells?" << endl << "1) Normal cells" << endl << "2) Cancer cells" << endl;
	cin >> select;

	while ((select != 1) && (select != 2)) {
		cout << "That's not an option" << endl;
		cout << "Please select a valid option:" << endl << "normal cells -> 1" << endl << "cancer cells -> 2" << endl;
		cin >> select;
	}

	cout << "What is the confluency percentage? " << endl;
	cin >> p;
	while ((p <= 0) || (p > 100)) {
		cout << "Enter a valid  percentage > ";
		cin >> p;
	}
	getline(cin, trash);

	board.seed_cells(select, p);

	system("cls");

	while (c != 'q') {
		system("cls");
		cout << "time: " << board.get_time() << endl;
		cout << "number of cells: " << board.get_num_cells() << endl;
		board.display();
		c = cin.get();
		board.next_state();
	}

	return 0;
}

void Board::seed_cells(int select, double p) {

	Cell* ptr;
	p = p / 100;
	srand(1);

	for (int x = 0; x < 20; x++) {
		vector<Cell*> row; // add empty row
		for (int y = 0; y < 75; y++) {
			if (select ==1)
				ptr = new Cell(0, ' ');
			else //initialise the board with dead cells
				ptr = new Cancer(0, ' ');
			row.push_back(ptr); // fill each 75 cell pointer vec
		}
		b.push_back(row); // fill 20 of type vector cell pointer
	}

	for (int x = 0; x < b.size(); x++) {
		for (int y = 0; y < b[x].size(); y++) {
			double r = rand() / double(RAND_MAX); //generates a random number between 0 and 1
			if (r < p) { //if random number < the confluency percentage then the cell becomes alive
				if (select == 1) 
				{
					b[x][y]->set_type('O');
					b[x][y]->set_alive(1);
				}
				else if (select == 2) 
				{
					b[x][y]->set_type('X');
					b[x][y]->set_alive(1);
					}
				}
			}
		}
}

int Board::get_time() {
	time++; //every time this function is called in main, the time increases
	return time;
}

int Board::get_num_cells() {
	int counter = 0;
	for (int x = 0; x < b.size(); x++) {
		for (int y = 0; y < b[x].size(); y++) {
			if (b[x][y]->get_alive() == 1) { //count number of alive cells
				counter++;
			}
		}
	}
	return counter;
}

void Board::display() {
	for (int x = 0; x < b.size(); x++) {
		for (int y = 0; y < b[x].size(); y++) {
			cout << b[x][y]->get_type();
		}
		cout << endl;
	}
}

int Board::neighbouring(int x, int y){
	int counter = 0;
	//run two loops to check for neighbours around a cell
	for (int t = -1; t < 2; t++)
	{
		for (int f = -1; f < 2; f++)
		{
			if ((x + t) >= 0 && (x + t) <= 19 && (y + f) >= 0 && (y + f) <= 74) //don't include the spaces outside the board
			{
				if ((b[x + t][y + f]->get_type() == 'O') || (b[x + t][y + f]->get_type() == 'X'))
				{
					counter++; //counts number of neighbours
				}
			}
		}
	}
	return counter;
}

void Board::next_state() {
	int count;
	for (int x = 0; x < b.size(); x++)
	{
		for (int y = 0; y < b[x].size(); y++)
		{

			count = neighbouring(x, y); // this is the number of cells surrounding of the O
			b[x][y]->neighbours(count); // change the value of alive in each cell correspnding to the neighbours

		}
	}
}

