// Program to implement a phone directory
//Group 1: Seymone Gugneja, Alejandro Cruz-Bautista, George Garrelts, Steven Lopez, Coy Raig, Xavier Floyd

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
using namespace std;

const int BUFFERSIZE = 30;	// Maximum size for a name/category
const int PHONESIZE = 13;	// Maximum size for a phone number

// Structure used to define a phone directory entry
struct PDEntry
{
	char name[BUFFERSIZE];
	char phone[PHONESIZE];
	char category[BUFFERSIZE];
};

// type definition to define the data type for the list data
typedef PDEntry ListItemType;

// create the node structure
struct Node
{
	ListItemType item;
	Node* next;
};

// Function initializations

// Load from file
void loadFromFile(Node*& head, Node*& lastNode);

// Adds entry to the back
// &head is a reference to the start of the list
// &lastNode is the reference to the last entry
// data is getting added to the list
// Returns true if successful, or false if not
bool addToList(Node*& head, Node*& lastNode, ListItemType data);

// Returns index of desired entry for other function to use
// &head is a reference to the start of the list
int findEntry(Node*& head);

// Changes entry from User's prompted name, phone, and group
// &head is a reference to the start of the list
void changeEntry(Node*& head);

// Displays all contacts from User's list
// &head is a reference to the start of the list
void displayAll(Node*& head);

// Displays contacts from a specific category
// &head is a reference to the start of the list
void displayCategory(Node*& head);

// Removes entry given by the user
// &head is the reference to the first entry
// &lastNode is the referece to the last entry
// data is getting removed from the list
void removeEntry(Node*& head, Node*& lastNode);

int main()
{
	int choice;
	// starts initializing the head of linked list to value NULL
	Node* head = NULL;
	Node* lastNode = NULL;
	ListItemType data;
	loadFromFile(head, lastNode);

	do
	{
		cout << "1. Add Entry\n";
		cout << "2. Change Entry\n";
		cout << "3. Display Names in Category\n";
		cout << "4. Display All\n";
		cout << "5. Remove Entry\n";
		cout << "6. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			cout << "\tWhat is the new name?";
			cin.getline(data.name, BUFFERSIZE);
			cout << "\tWhat is the new number?";
			cin.getline(data.phone, PHONESIZE);
			cout << "\tWhat is the category?";
			cin.getline(data.category, BUFFERSIZE);

			addToList(head, lastNode, data);
			break;
		case 2:
			changeEntry(head);
			break;
		case 3:
			displayCategory(head);
			break;
		case 4:
			displayAll(head);
			break;
		case 5:
			removeEntry(head, lastNode);
			break;
		case 6: 
			//saveExitfile(head, lastNode);
			break;
		}

	} while (choice != 6);

	while (head != NULL)
	{
		Node* temp = head->next;
		delete head;
		head = temp;
	}
	return 0;
}


// Menu to find desired entry
int findEntry(Node*& head)
{
	Node* temp = head;
	int counter = 1;

	while (temp != NULL)
	{
		printf("\t%d. %-34s", counter, temp->item.name);
		printf("%-15s%-10s\n", temp->item.phone, temp->item.category);
		

		counter++;
		temp = temp->next;
	}

	cout << "\tGive the number of the desired contact\n";

	int userInput;
	cin >> userInput;
	cin.ignore();
	return userInput;
}


// Adds new entry to back
bool addToList(Node*& head, Node*& lastNode, ListItemType data)
{
	Node* temp = new Node;
	if (temp == NULL) return false;
	temp->item = data;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		lastNode = temp;
	}
	else
	{
		lastNode->next = temp;
		lastNode = temp;
	}

	return true;
}


// Changes entry from User's prompted name, phone, and group
void changeEntry(Node*& head)
{
	// Variable declarations
	int userChoice;
	int index;
	Node* temp = head;

	// Finds desired entry
	index = findEntry(head);

	// Converts index into entry
	for (int x = 1; x < index; x++)
	{
		temp = temp->next;
	}

	// Sub menu
	printf("1. %s\n", temp->item.name); 
	printf("2. %s\n", temp->item.phone); 
	printf("3. %s\n", temp->item.category);

	//user will enter the line number
	cout << ("What do you want to change?");
	cin >> userChoice;

	//user will enter updated info and overwrite the current stored info
	if (userChoice == 1)
	{
		printf("Enter a new name: ");
		cin.getline(temp->item.name, BUFFERSIZE);
	}
	else if (userChoice == 2)
	{
		printf("Enter a new phone number: ");
		cin.getline(temp->item.phone, PHONESIZE);
	}
	else if (userChoice == 3)
	{
		printf("Enter a new category: ");
		cin.getline(temp->item.category, BUFFERSIZE);
	}
	else
	{
		cout << ("Invalid choice.");
	}
}


// Displays all contacts from User's list
void displayAll(Node*& head)
{
	// Prints the current directory to the screen
	cout << "Directory:	\n";
	cout << '\n';

	Node* temp = head;
	while (temp != NULL)
	{
		int counter = 1;
		printf("\t%-20s", (temp->item).name);
		printf("%-20s%-10s\n", (temp->item).phone, (temp->item).category);
		counter++;
		temp = temp->next;
	}
	cout << '\n';
}


// reads name, number, and category from text file 
// also displays error code if file is not opened. 
void loadFromFile(Node*& head, Node*& lastNode)
{
	ifstream inFile;
	const int FILENAMESIZE = 9;
	const char FILENAME[FILENAMESIZE] = "data.txt";
	ListItemType data;

	// open file from data.txt
	inFile.open(FILENAME);

	// check to see if the file can be opened.
	if (!inFile)
	{
		cerr << "Data file cannot be opened. Starting from scratch.\n";
	}
	// while loop to ensure the file reads to the end and doesn't
	// go past end of file. Also peeks at the next character
	// in file to negate an extra blank node in the list.
	while (inFile && !inFile.eof() && inFile.peek() != EOF)
	{
		inFile.getline(data.name, BUFFERSIZE);
		inFile.getline(data.phone, PHONESIZE);
		inFile.getline(data.category, BUFFERSIZE);
		// Converts file data into linked list
		addToList(head, lastNode, data);
	}
}


// Displays contacts from a specific category
void displayCategory(Node*& head)
{
	Node* temp = head;
	char catInput[BUFFERSIZE];
	cin.getline(catInput, BUFFERSIZE);

	while (temp != NULL)
	{
		if (strncmp(temp->item.category, catInput, BUFFERSIZE) == 0)
		{
			// Display this entry
			printf ("\t%-20s%-20s", temp->item.name, temp->item.phone);
			printf ("%-10s\n", temp->item.category);
		}
		temp = temp->next;
	}
}

// Removes entry given by the user
void removeEntry(Node*& head, Node*& lastNode)
{
	
	if (head == NULL)
	{
		cout << "There is nothing to remove\n";
		return;
	}

	Node* temp = head->next;
	Node* prev = head;

	// Figure out desired contact to delete
	int index = findEntry(head);
	
	for (int x = 1; x < index; x++)
	{
		prev = prev->next;
		temp = prev->next;
	}
	if (temp->next == NULL)
	{
		lastNode = prev;
	}
	else
	{
		prev->next = temp->next;
	}
	delete temp;
}
