#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Minesweeper.h"

int Minesweeper::gridSize = 5;  // hardcoded to a 5x5 grid

void Minesweeper::Menu()
{
    clrscr();
    bool status;
    int menu;
    cout << "\n=========== MENU ===========" << endl;
    cout << "1.Play Game" << endl;
    cout << "2.How to Play" << endl;
    cout << "3.About" << endl;
    cout << "4.Quit" << endl;
    cout << "\nPlease choose a menu option(1,2,3,4): ";
    cin >> menu;
    while(menu != 1 && menu != 2 && menu != 3 && menu != 4|| cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid entry. Please enter 1, 2, 3 or 4: ";
        cin >> menu;
    }
    clrscr();
    switch(menu)
    {
        case 1:
            cin.ignore(1000, '\n');
            break;
        case 2:
            How_To_Play();
	    cin.ignore(1000, '\n');
            Menu();
            break;
        case 3:
            About();
	    cin.ignore(1000, '\n');
            Menu();
            break;
        case 4:
            cin.ignore(1000, '\n');
            cout << "\nAre you sure you want to quit?(Y/N)? ";
            status = Verify();
            if(status == true)
                exit(1);
            else if(status == false)
                Menu();
        default:
            break;
    }

}

void Minesweeper::How_To_Play()//function prints out rules for the game.
{
    cout << "\n============== RULES ================";
    cout << "\n-Locate mines in the empty cells.";
    cout << "\n-Each numbered cell describes the number of mines that the cell is adjacent to.";
    cout << "\n-Cells are considered adjacent if they share either a side or a corner.";
    cout << "\n-No cell contains more than one mine, and numbered cells never contain mines.";
    cout << "\n-Identify the cell by giving the row and column entry separated by space." ;
    cout << "\n-Remember that rows are horizontal and columns are vertical " << endl;
    cout << "\nPress ENTER to continue...";
    cin.get();
}

void Minesweeper::About()//function prints out the information about the game
{
    cout << "\n=========== Minesweeper 1.0 ===========\n";
    cout << "\n-The Game Developers: \n";
    cout << "\n-Arslan Sana: Game's Logic & Design";
    cout << "\n-Emily Chan: Grid Design";
    cout << "\n-Daniil Stepanov: Menu Design & Implementation";
    cout << "\n-Alexei Tontici: Class Header & Class Implementation Files & Design";
    cout << "\n-Mohsan Shahbaz: Testing and Code Review";
    cout << "\n-David Pishchik: Testing and Code Review\n";
    cout << "\nPress ENTER to continue...";
    cin.get();
}

bool Minesweeper::Verify()//function, after input validation checked, transfers 'Y' or 'N' to true or false.
{
    char reply;
    cin >> reply;
    while(toupper(reply) != 'Y' &&  toupper(reply) != 'N')
    {
        cin.ignore(1000, '\n');
        cout << "Please enter Y for 'YES' or N for 'NO': ";
        cin >> reply;
    }
    if(toupper(reply) == 'Y')
        return true;
    else if(toupper(reply) == 'N')
        return false;
}

int Minesweeper::Get_Difficulty_Level()
{
    int level;
    string name;
    cout << "\nPlay Game Selected\n" << endl;
    cout << "Please enter your name: ";
    getline(cin, name);
    set_playerName(name);
    clrscr();
    cout << "\nHi, " << name << "! Please choose the difficulty level: " << endl;


    cout << "\n1. Normal (press 1 and ENTER)\n";
    cout << "2. Hard (press 2 and ENTER)\n\n";

    cout << "Difficulty level: ";
    cin >> level;
    while(level != 1 && level != 2 || cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid entry. Please enter 1 or 2: ";
        cin >> level;
    }
    clrscr();
    cout << "Player: " << get_playerName() << endl;
    cout << "You've picked difficulty level: ";
    switch(level)
    {
        case 1: cout << "NORMAL";
            break;
        case 2: cout << "HARD";
            break;
        default: cout << "NORMAL";
            break;
    }
    return level;
}

void Minesweeper::Create_Random_Grid(vector<vector<int> > &intGrid, int ROWS, int COLUMNS)
{
    srand(time(0));

    int numMines = 0;
    const int LIMIT = ROWS*COLUMNS/3 + 1; // Limit mines to 9

    // Assigns 'mines' randomly to some squares
    // The number of mines will always end up being 9
    while(numMines != LIMIT)
    {
        for(int i=0; i<ROWS; i++)
        {
            for(int j=0; j<COLUMNS; j++)
            {
                int randN = (rand()%10)+1;
                if(intGrid[i][j] == -1)
                    continue;
                else if(randN == 3 || randN == 7 || randN == 10)
                {
                    intGrid[i][j] = -1; // mines are -1's
                    numMines++;
                        break;
                }
            }

            if(numMines == LIMIT)
                break;
        }
    }

    int adjacentMines;

    // Now our grid has 9 mines (-1's) in random squares. All other squares are still -2's
    // We have to change those -2's to appropriate numbers based on how many mines there are adjecent to that square
    // This second nested loop look at each square holding a -2 (i.e. not a mine)
    // However many mines (i.e. -1's) are adjacent to that square, that is the number assigned to it
    // ex: If we see that a particular square holding a -2 has a -1 above it, below it, and to its top right corner,
    // we assign the number '3' to that square. This square is no longer holding a -2.
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLUMNS; j++)
        {
            adjacentMines = 0;
            if(intGrid[i][j] != -2)
                continue;
            else if(intGrid[i][j] == -2)
            {
                // checks squares surroduning top left corner
                if(i == 0 && j == 0)
                {
                   if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                   if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                   if(intGrid[i+1][j+1] == -1)
                        adjacentMines++;
                }

                // top right corner
                if(i == 0 && j == COLUMNS-1)
                {
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j-1] == -1)
                        adjacentMines++;
                }

                // bottom left corner
                if(i == ROWS-1 && j == 0)
                {
                    if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j+1] == -1)
                        adjacentMines++;
                }

                // bottom right corner
                if(i == ROWS-1 && j == COLUMNS-1)
                {
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                }

                // top edge
                if( i == 0 && j != 0 && j != COLUMNS-1)
                {
                    if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j-1] == -1)
                        adjacentMines++;
                }

                // bottom edge
                if(i == ROWS-1 && j != 0 && j != COLUMNS-1)
                {
                    if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j-1] == -1)
                        adjacentMines++;
                }

                // left edge
                if(j == 0 && i != 0 && i != ROWS-1)
                {
                    if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j+1] == -1)
                        adjacentMines++;
                }

                // right edge
                if(j == COLUMNS-1 && i != 0 && i != ROWS-1)
                {
                    if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j-1] == -1)
                        adjacentMines++;
                }


                // all other possible squares to be checked
                if(i !=0 && i!= ROWS-1 && j != 0 && j != COLUMNS-1)
                {
                    if(intGrid[i][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j+1] == -1)
                        adjacentMines++;
                    if(intGrid[i+1][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j-1] == -1)
                        adjacentMines++;
                    if(intGrid[i-1][j+1] == -1)
                        adjacentMines++;
                }
                intGrid[i][j] = adjacentMines; // assign number of mines adjecent to that square
            }
        }
    }
}

void Minesweeper::Play_Game(vector<vector<int> > &intGrid, vector<vector<string> > &blankGrid, vector<vector<string> >&savedGrid, int ROWS, int COLUMNS, int level)
{
    cout << "\n ====== Minesweeper ======\n\n";

    // print grid created in above function

    cout << " ROW" << endl;
    cout << "    ---------------------" << endl; // This prints the top dashed line of the grid.
    for(int i=0; i<ROWS; i++)
    {
        cout << "  "  << i+1;

        for(int j=0; j<COLUMNS; j++)
        {
            int randN = (rand()%100)+1;
           if(intGrid[i][j] == -1 || randN%10==0 || randN%8 == 0 || randN%11==0)
            {
                cout << setw(3) << "| " << blankGrid[i][j];
                savedGrid[i][j] = blankGrid[i][j]; // save this randomly created square as a blank square
            }

            else
            {
                cout << setw(3) << "| " << intGrid[i][j];
                savedGrid[i][j] = Int_to_String(intGrid[i][j]); // save this randomly created square as it is
		// converting the int to string first is necessary as the savedGrid is of type string
		// NOTE: the mines in the savedGrid will be X's. This is what the user will see as mines.
		// the -1's were for our own use.
		}
        }
        cout << setw(3) << "| "; // this is what I used to make the individual squares the numbers are int
        cout << endl;
        cout << "    ---------------------"; // this make the dashed line forming the rows
        cout << endl;
    }
    cout << "      ";
    for (int nrow = 1; nrow <= ROWS; nrow++)
        cout << nrow << "   ";
    cout << "COLUMN\n" ;


    int row, column; // coordinates entered by user stored in these two variables
    int minesFound = 0;

    int tries, actualMines = Get_Number_of_Mines(intGrid, ROWS, COLUMNS);

    // Level entered by user determined the number of guess he has to find all mines
    if(level == 1)
        tries = actualMines + 2; // Easy. User can have up to 2 wrong guesses and still be able to find all mines
    else if(level == 2)
        tries = actualMines ; //Hard. No mistakes. User must successfully find a mine on EVERY guess to find all mines.


    cout << "\nFind all the mines in the grid above within " << tries << " guesses.\n";
    // Loop allows the user to guess the mines 1 at a time for a limited number of guesses
    for(int n=1; n<=tries; n++)
    {
        if(n != tries)
            cout << "\nYou have " << tries+1 - n << " guess left.";
        else if(n == tries)
            cout << "\nThis is your final guess!";
        cout << "\nGuess " << n << " - ";
        cout << "Enter row followed by column # (separated by space or ENTER): ";
        cin >> row >> column;
        // input validation for row and column #'s
        bool condition = true;
        while(condition)
        {
            if(row-1 >= ROWS || column-1 >= COLUMNS || row-1 < 0 || column-1 < 0 || cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a valid number between 1 and " << ROWS << " for both: ";
            }

            // If user enters coordinate thats already an uncovered mine
            else if(savedGrid[row-1][column-1] == "X")
                cout << "You already found that mine! Try again: ";

            // if user enters coordinate that is already a given number in the grid
            else if(savedGrid[row-1][column-1] != " " && intGrid[row-1][column-1] != -1)
                cout << "This square is already a given number!\nPlease enter row and column # for a blank square: ";

            else condition = false;

            if(condition)
                cin >> row >> column;

        }
        cin.ignore(1000, '\n'); // ignores any additional garbage entered by user

        cout << "\n";
        clrscr();
        cout << "Player: " << get_playerName() << endl;
        cout << "\nYou entered: " << row << " " << column;
        int a, b;
        // if coordinate entered are a mine
        if(intGrid[row-1][column-1] == -1)
        {
            a = row-1;
            b = column-1;

            cout << "\nCorrect!" << endl;
            minesFound++;
        }

        else cout << "\nIncorrect!" << endl;

        if(n != tries)
            cout << "Total mines found so far: " << minesFound << endl;

        cout << "\n ====== Minesweeper ======\n\n";
        Reprint_Grid(savedGrid, ROWS, COLUMNS, a, b); // Reprint grid after every guess

        // If all mines found before guess limit is reached, break out of loop
        if(minesFound == actualMines && tries > actualMines)
            break;

    }

    // if all mines found
    if(minesFound == actualMines)

    {   cout << "\nWOW, YOU GOT ALL OF THEM!";
        cout << "\nTotal mines found: " << minesFound << endl;
        cout << "\nBelow is the completed grid: " << endl;
        Print_Solved_Grid(savedGrid, intGrid, ROWS, COLUMNS);
    }

    // If NOT all mines found
    else if(minesFound < actualMines)
    {
        cout << "\nGAME OVER!";
        cout << "\nTotal mines found: " << minesFound << endl;
        cout << "\nBelow is the completed grid. \nThe X's are the mines you successfully found.\nThe M's are the mines you missed. " << endl;
        Print_Solved_Grid(savedGrid, intGrid, ROWS, COLUMNS);
    }

}

// This function simply reprints the saved random grid
void Minesweeper::Reprint_Grid(vector<vector<string> >&savedGrid, int ROWS, int COLUMNS, int a, int b)
{
    cout << " ROW" << endl;
    cout << "    ---------------------" << endl;
    for(int i=0; i<ROWS; i++)
    {
        cout << "  "  << i+1;

        for(int j=0; j<COLUMNS; j++)
        {
            if(i == a && j == b)
                savedGrid[i][j] = "X";

            cout << setw(3) << "| " << savedGrid[i][j];
        }

        cout << setw(3) << "| ";
        cout << endl;
        cout << "    ---------------------";
        cout << endl;
    }
    cout << "      ";
    for (int nrow = 1; nrow <= ROWS; nrow++)
        cout << nrow << "   ";
    cout << "COLUMN\n" ;
}

// This function prints the complete grid (with all numberrs filled in) at the end of the game
void Minesweeper::Print_Solved_Grid(vector<vector<string> >&savedGrid, vector<vector<int> >&intGrid, int ROWS, int COLUMNS)
{
    cout << "\n";

    cout << "   ---------------------" << endl;
    for(int i=0; i<ROWS; i++)
    {
        cout << "  ";
        for(int j=0; j<COLUMNS; j++)
        {
            if(intGrid[i][j] == -1 && savedGrid[i][j] != "X")
            {
                savedGrid[i][j] = "M";
                cout << setw(3) << "| " << savedGrid[i][j];
            }

            else if(intGrid[i][j] == -1 && savedGrid[i][j] == "X")
                cout << setw(3) << "| " << savedGrid[i][j];


            else cout << setw(3) << "| " << intGrid[i][j];
        }

        cout << setw(3) << "| ";
        cout << endl;
        cout << "   ---------------------";
        cout << endl;
    }
}

// converts int to string using stringstreams
string Minesweeper::Int_to_String(int a)
{
    ostringstream convert;
    convert << a;

    return convert.str();
}

// Functions finds number of mines in the grid and returns it
int Minesweeper::Get_Number_of_Mines(vector<vector<int> > &intGrid, int ROWS, int COLUMNS)
{
    int mines = 0;

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLUMNS; j++)
        {
            if(intGrid[i][j] == -1)
                mines++;
        }
    }

	return mines;
}
