//Authors Matthew, Juan, Connor, Nick, Sepehr, Ahmed
// Life simulation

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

//Global constants used throughout the program  
const int MAXWORLDROWS = 25;
const int MAXWORLDCOLS = 80;
const int MAXROWS = MAXWORLDROWS + 2;
const int MAXCOLS = MAXWORLDCOLS + 2;
const int FILENAMESIZE = 255;

// ASCII characters to use for display
// https://theasciicode.com.ar/extended-ascii-code/block-graphic-character-ascii-code-219.html
// for interesting effect use code 219 and 176 instead of the asterisk and space
const unsigned char CELL = '*';  // 219;
const unsigned char EMPTY = ' '; // 176;

//Enumeration which is used to choose from either dead (0) or alive (1)
enum class State { dead = 0, alive = 1 };

/*
* initWorld is used to initialize all positions in the world
* array to the 'dead' state
*/
void initWorld(State world[][MAXCOLS]);

/*
* display is used to draw the 'world' onto the screen
* for each 'alive' cell, the value CELL is displayed
* for each 'dead' cell, the value EMPTY is displayed
* does NOT display any items in:
*   row 0, row MAXROWS-1, column 0, or column MAXCOLS-1
* since these rows and columns are used as a "border"
* around the world grid
*/
void display(State world[][MAXCOLS]);

/*
* getFile will get a filename from the user. It then attmpts
* to open the file, read its contents, and update the world
* based on the contents of the file. The file should contain
* only spaces and asterisks. A space represents a 'dead' cell
* and an asterisk represents an 'alive' cell.
* The function stops reading and exits the program if > MAXWORLDCOLS
* characters are found on one row, or if > MAXWORLDROWS rows are
* found in the file.
*/
void getFile(State world[][MAXCOLS]);

/*
* calcNewWorld is used to calculate the new state of the world
* (i.e. a new generation) based upon analyzing the current world state
*/
void calcNewWorld(State world[][MAXCOLS]);

/*
* neighborCount is used to count the number of 'alive' cells in
* the 8 neighboring positions which are surrounding position
* [row][col] in world
*/
int neighborCount(State world[][MAXCOLS], int row, int col);

int main()
{
	//arrays initialized
	State world[MAXROWS][MAXCOLS];
	char inputKeyboard[FILENAMESIZE];

	int generation = 0;
	bool stop = false;
	
	//world[2][3] = State::alive	
	initWorld(world);

	//calls getFile function.
	getFile(world);

	do
	{
		// system("cls") clears the screen; only works on Windows machines
		// You will probably need to comment this out if working on
		// a non-Windows machine
		system("cls");

		display(world);
		generation++;
		cout << "Generation: " << generation << "\t";
		cout << "<ENTER> to continue / <Q + ENTER> to quit: ";
		
		// TODO: get input from user and decide whether to quit the loop
		// and whether to compute a new generation		
		cin.getline(inputKeyboard, FILENAMESIZE);
		if (inputKeyboard[0] == 'q' || inputKeyboard[0] == 'Q') {
			stop = true;
		}
		else
		{
			calcNewWorld(world);
		}
	} while (!stop);

	return 0;
}

int neighborCount(State world[][MAXCOLS], int row, int col)
{	
	int i = 0;
	if (row < 1 || row > MAXWORLDROWS)
	{
		cerr << "ERROR: invalid row parameter " << row << " in neighborCount\n";
		exit(1);
	}
	else if (col < 1 || col > MAXWORLDCOLS)
	{
		cerr << "ERROR: invalid col parameter " << col << " in neighborCount\n";
		exit(1);
	}
	else
	{
		//Moved nested for loop to else statement. Could be wrong about that. -Matt
		//Might count the center cell. Need to fix.
		for (int f = row - 1; f < row + 2; f++) {
			for (int k = col - 1; k < col + 2; k++) {
				if (world[f][k] == State::alive) {
					i++;
				}
			}
		}
		if (world[row][col] == State::alive) {
			i--;
		}
	}

	//if (world[row][col])

	return i;
}

//Purpose: calculate the new state of the world (generation) based on current state. 
//function doesn't return any value.
void calcNewWorld(State world[][MAXCOLS])
{
	State count[MAXROWS][MAXCOLS];
	for (int x = 1; x <= MAXWORLDROWS; x++) {
		for (int y = 1; y = MAXWORLDCOLS; y++) {
			int aliveNum = neighborCount(world, x, y);
			if (aliveNum == 0 || aliveNum == 1) {
				count[x][y] = State::dead;
			}
			else if (aliveNum == 2) {
				count[x][y] = world[x][y];
			}
			else if (aliveNum == 3) {
				count[x][y] = State::alive;
			}
			else {
				count[x][y] = State::dead;
			}
		}
	}
	//FOR loop that ...
	for (int x = 1; x <= MAXWORLDROWS; x++) {
		for (int y = 1; y <= MAXWORLDCOLS; y++) {
			world[x][y] = count[x][y];
		}
	}
}

void getFile(State world[][MAXCOLS])
{

	int row = 1;
	char inputfile[FILENAMESIZE];
	int usedsize = 0;
	char tempRow[MAXWORLDCOLS + 1];


	printf("Enter the filename containing the initial structure: ");

	ifstream inFile;
	cin.getline(inputfile, FILENAMESIZE);
	inFile.open(inputfile);
	
	if (!inFile.is_open()) {
		exit(EXIT_FAILURE);
	}
	//while (usedsize < MAXWORLDCOLS && getline(inFile, tempRow[0], '\n'))
	while (usedsize < MAXWORLDCOLS && inFile >> tempRow[0] );
	{
		usedsize++;
	}



	// BH: Have you guys looked at the ReadingFiles.cpp class demo file?
	// What is supposed to be the NEXT step after opening a file?

	// Make sure row is incremented each time you read a line from the file

	
	char rowTemp[MAXWORLDCOLS + 1];

	/*for (int r = 0; r < MAXWORLDROWS; r++) {
		cin.getline(inFile, rowTemp[MAXWORLDROWS], "\n");
			for (int c = 1; c < MAXWORLDCOLS + 1; c++) {
				if (rowTemp[c - 1] == "*") {
					world[r][c] = State::alive;
				}
				else {
					world[r][c] = State::dead;
				}

			}

	}
	*/
	// After file reading is finished, this code checks to see if the reading stopped
	// because of too many characters on a line in the file, or too many rows in the file
	// It is possible that you might have to change the conditions here depending on
	// exactly how you choose to read the file
	if (!inFile.eof())
	{
		if (row <= MAXWORLDROWS)
		{
			cerr << "\nERROR: Line " << row << " in input file contains more than " << MAXWORLDCOLS << " chars\n";
		}
		else
		{
			cerr << "\nERROR: There are more than " << MAXWORLDROWS << " lines in the file\n";
		}
		//outside of if to print with other error messages?
		cerr << "\nERROR: input file cannot be opened.";

		inFile.close();
		exit(1);
	}

	inFile.close();
}

//Purpose: used to display the current "Life" generation to user.
//doesn't return any value.
void display(State world[][MAXCOLS])
{	
	//nested for loop will set the array to either EMPTY or CELL for values. 
	for (int x = 1; x < MAXWORLDROWS; x++){
		for (int y = 1; y < MAXWORLDCOLS; y++){
			if (world[x][y] == State::dead) {
				printf("%c", EMPTY);
			}
			else{
				printf("%c", CELL);
			}
		}
		printf("\n");
	}
}

//Purpose: initializes all positions in the world array to the dead state or '0'
//returns nothing.
void initWorld(State world[][MAXCOLS])
{
	//nested for loop is used to make all the array be set to dead.
	for (int i = 0; i < MAXROWS; i++) 
	{
		for (int k = 0; k < MAXCOLS; k++) 
		{
			world[i][k] = State::dead;
		}
	}
}