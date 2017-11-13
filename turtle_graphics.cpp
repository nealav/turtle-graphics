#include <iostream>
#include <cstdlib>
#include <ctime> //for rand-seeding
#include <string> //string usage
#include <sstream> //sort-function stoi conversion
#include <iomanip> //for different cin.() functions
#include <stdio.h> //scanf
#include <conio.h> //getch

using namespace std;

enum Direction {North, South, East, West};
enum Direction facing = East;
enum Command {PenUp, PenDown, TurnRight, TurnLeft, MoveForward, Print, EndofData};
enum Command penCommand = PenDown;
enum Command executeCommand;
static int boardArray[20][20];
static char printArray[20][20];
static int commandsArray[100][2]; //max amount of commands is 100 before undefined behavior starts, dynamic allocation of arrays requires redefinition of new array pointers as well as several accessory functions
//to addONE, deallocate from memory, redistribute and point to parallel print arrays, making it severely beyond the scope of this assignment.
int commandChoice;
char menuChoice;
int commandCounter = 0;
int x = 0, y = 0;

void commandTester()
{
    for(int i = 0; i < 10; i++) {
            cout << endl;
        for(int j = 0; j < 2; j++) {
            cout << commandsArray[i][j] << " ";
        }
    }
}

void commandMenu()
{
    cout << "Turtle starts at the upper-left corner facing East." << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Enter commands -- one command per line." << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "1   = <Pen Up>" << endl;
    cout << "2   = <Pen Down>" << endl;
    cout << "3   = <Turn Right>" << endl;
    cout << "4   = <Turn Left>" << endl;
    cout << "5,X = <Move X Spaces>" << endl;
    cout << "6   = <Print>" << endl;
    cout << "9   = <End of Program>" << endl;
    cout << "------------------------------------------------------------" << endl;
}

void arrayInitializer()
{
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            boardArray[i][j] = 0;
        }
    }
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 2; j++) {
            commandsArray[i][j] = 0;
        }
    }
}

void addToArrayRow (int commandNumber, int command, int commandArray[][2])
{
    commandArray[commandNumber][0] = command;
}

void addToArrayCol (int commandNumber, int command, int commandArray[][2])
{
    commandArray[commandNumber][1] = command;
}


void commandReciever()
{
    while (true)
    {
        if (commandChoice == 9) {
            break;
        }

    cout << "Command #" << commandCounter << "> ";
    cin >> commandChoice;
    while (cin.fail()) {
        cout << "NAN" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> commandChoice;
    }



        switch (commandChoice)
        {
            case 1: //Pen Up
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 2: //Pen Down
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 3: //Turn Right
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 4: //Turn Left
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 5: //Move X Spaces
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                cin.ignore(100,',');
                cin >> commandChoice;
                while (cin.fail()) {
                    cout << "NAN" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> commandChoice;
                }
                addToArrayCol(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 6: //Print
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            case 9: //End of Data
                addToArrayRow(commandCounter, commandChoice, commandsArray);
                commandCounter++;
                continue;

            default:
                cout << "Invalid Command." << endl;
                continue;
        }
    }
}


void moveForward(enum Direction facing, int spaces, int boardArray[][20])
{
    //Movement if pen is up b[y][x]

    if (penCommand == PenUp && facing == North) {
        y -= (spaces-1);
    }
    else if (penCommand == PenUp && facing == South) {
        y += (spaces-1);
    }
    else if (penCommand == PenUp && facing == East) {
        x += (spaces-1);
    }
    else if (penCommand == PenUp && facing == West) {
        x -= (spaces-1);
    }

    //Movement if pen is down
    else if (penCommand == PenDown && facing == North) {

		for (int i = 0; i < spaces; i++)
		{
			boardArray[y-i][x]=1;

		}
		y -= (spaces-1);
    }
    else if (penCommand == PenDown && facing == South) {

		for (int i = 0; i < spaces; i++)
		{
			boardArray[y+i][x]=1;

		}
        y += (spaces-1);
    }
    else if (penCommand == PenDown && facing == East) {

		for (int i = 0; i < spaces; i++)
		{
			boardArray[y][x+i]=1;

		}
        x += (spaces-1);
    }
    else if (penCommand == PenDown && facing == West) {

		for (int i = 0; i < spaces; i++)
		{
			boardArray[y][x-i]=1;

		}
        x -= (spaces-1);
    }


}

void turnRight()
{
    if (facing == North) {
        facing = East;
    }
    else if (facing == South) {
        facing = West;
    }
    else if (facing == East) {
        facing = South;
    }
    else if (facing == West) {
        facing = North;
    }
    else { cout << "Boundary" << endl; }
}

void turnLeft()
{
    if (facing == North) {
        facing = West;
    }
    else if (facing == South) {
        facing = East;
    }
    else if (facing == East) {
        facing = North;
    }
    else if (facing == West) {
        facing = South;
    }
    else { cout << "Boundary" << endl; }
}


void print()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (boardArray[i][j] == 1) {
                printArray[i][j] = '*';
            }
            else {
                printArray[i][j] = ' ';
            }
        }
    }

    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
                cout << printArray[i][j];
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------" << endl;

}

void commandExecuter()
{
    for (int i = 0; i < commandCounter; i++)
    {
        if (executeCommand == EndofData) {break;}

        switch(commandsArray[i][0])
        {
            case 1:
                penCommand = PenUp;
                continue;
            case 2:
                penCommand = PenDown;
                continue;
            case 3:
                executeCommand = TurnRight;
                turnRight();
                continue;
            case 4:
                executeCommand = TurnLeft;
                turnLeft();
                continue;
            case 5:
                executeCommand = MoveForward;
                moveForward(facing,commandsArray[i][1],boardArray);
                continue;
            case 6:
                executeCommand = Print;
                print();
                continue;
            case 9:
                executeCommand = EndofData;
                continue;
            default:
                continue;
        }
    }
}


/* void mainMenu()
{
    cout << "Press Enter to load a new program or 'q' to Quit. " << endl;
    cin >> menuChoice;
    while (cin.fail()) {
        cout << "Invalid entry. " << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> commandChoice;
    }
 while (true) {
    if (menuChoice == '\n')
    {
        commandCounter = 0; penCommand = PenDown; x = 0; y = 0; facing = East;
        commandMenu();
        arrayInitializer();
        commandReciever();
        commandExecuter();
    }
    else if (menuChoice == 'q') {
        break;
    }
    else { cout << "Invalid entry. " << endl; continue; }
 }
} This function is for the sole purpose of looping over and over if the user wants that.
*/


int main()
{
    commandMenu();
    arrayInitializer();
    commandReciever();
    commandExecuter();
    return 0;
}
