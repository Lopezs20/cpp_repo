// This program simulates a purse of coins
//Seymone Gugneja, George Garrelts, Steven Lopez, Alejandro Cruz-Bautista, Coy Raig, Xavier Floyd

#include <iostream>
using namespace std;

// Create an enumeration data type called Coin
enum class Coin { penny = 1, nickel = 5, dime = 10, quarter = 25, error };

const int MAXSIZE = 15;
const int SENTINEL = 0;

int whatCoin;
int sum = SENTINEL;
int purseSize = 0;

//create array to hold all coins
Coin purse [MAXSIZE];


// Takes user input (1, 2, 3, 4) and converts it to a Coin
Coin ConvertToCoin(int x);

// Prints a word to the screen stating what the coin is
void PrintCoin(Coin x);

//Seymone and George
int main()
{
	// Main program code here
	//display menu
	cout << "Deposit coins into purse.  Enter: \n";
	cout << "1 to deposit penny: \n";
	cout << "2 to deposit nickel: \n";
	cout << "3 to deposit dime: \n";
	cout << "4 to deposit quarter: \n";
	cout << SENTINEL << " to stop\n";

	//user enters choices -- 0 to stop / max 15 -- use scanf, and an if statement that checks for 0
	for (int i = SENTINEL; i < MAXSIZE; i++)
	{

		cout << " ? ";
		cin >> whatCoin;


		if (whatCoin == SENTINEL) //print exit statement
		{
			break;
		}
		else
		{
			purse[i] = ConvertToCoin(whatCoin);
			if (purse[i] != Coin::error) 
			{
				sum += (int)purse[i];
				purseSize++;
			}
			else 
			{
				i--;
			}
		}
		if (purseSize == MAXSIZE)
		{
			printf("Purse is full\n");
		}
	} 

	
	//program prints coins and total
	cout << "Purse Contents: ";
	cout << "{";
	for (int i = 0; i < purseSize; i++)
	{
		PrintCoin(purse[i]);
		if (i != purseSize - 1)
		{
			cout << " ";
		}
	}
	cout << "}\n";
	printf("Total purse value : $%d.%d%d", (sum % 1000 - sum % 100)/100, (sum % 100 - sum % 10)/10, sum % 10);
	cout << "\n";
	return 0;
}

//Coy and Xavier
Coin ConvertToCoin(int x) 
{
	// Write your ConvertToCoin code here
	switch (x)
	{
	case 1:
		return Coin::penny;
		break;

	case 2:
		return Coin::nickel;
		break;

	case 3:
		return Coin::dime;
		break;

	case 4:
		return Coin::quarter;
		break;

	default:
		cout << "Invalid coin\n";
		return Coin::error;
		break;
	}

	return Coin::penny;
}

//Alejandro and Steve
void PrintCoin(Coin x)
{
	// Write your PrintCoin code here
	switch (x)
	{
	case (Coin)1:
		printf("penny");
		break;

	case (Coin)5:
		printf("nickel");
		break;

	case (Coin)10:
		printf("dime");
		break;

	case (Coin)25:
		printf("quarter");
		break;

	default:
		printf("error");
		break;
	}
}
