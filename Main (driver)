#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Minesweeper.h"

using namespace std;

// Prototype

int main()
{
    Minesweeper m1;
    m1.Menu();

    bool status;
    do{

        /*******************************************/
        /* int grid                                */
        /* This will be the initial grid of ints   */
        /* It will consist of of -1's (mines)      */
        /* and regular numbers                     */
        /*******************************************/
        vector<vector<int> > intGrid(m1.get_ROWS(), vector<int>(m1.get_COLUMNS(), -2));
        // Right now it is simply filled with -2's


        /*****************************************************************************/
        /* Blank space string grid                                                   */
        /* This is simply a grid of blanks (empty string)                            */
        /* It will be used along with the intGrid to make a single grid made         */
        /* up of numbers and blank squares. This is what the player will see.        */
        /* The 'blanks' will cover the -1's and as well as some other random numbers */
        /* This is the grid the player will see at the beginning of the game         */
        /*****************************************************************************/
        vector<vector<string> > blankGrid(m1.get_ROWS(), vector<string>(m1.get_COLUMNS(), " "));

        /***********************************************************************************/
        /* vector to save randomized grid to be reprinted later                            */
        /* Since we will be printing out the randomized grid after every row-column entry, */
        /* this grid will used to save the randomized grid and print it out                */
        /* in a separate function whenever needed                                          */
        /***********************************************************************************/
        vector<vector<string> > savedGrid(m1.get_ROWS(), vector<string>(m1.get_COLUMNS()));

        int level = m1.Get_Difficulty_Level();

        // Creates complete intGrid with -1's as mines
        m1.Create_Random_Grid(intGrid, m1.get_ROWS(), m1.get_COLUMNS());

        cout << "\n";

        // Prints grid by combining intGrid and blankGrid
        // Saves the randomly created grid in savedGrid (so it can be reprinted later)
        // Game is played here
        m1.Play_Game(intGrid, blankGrid, savedGrid, m1.get_ROWS(), m1.get_COLUMNS(), level);

        cout << "\nWould you like to play again(Y/N)? ";
        status = m1.Verify();
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "\n";

    }while(status == true);

    return 0;
}
