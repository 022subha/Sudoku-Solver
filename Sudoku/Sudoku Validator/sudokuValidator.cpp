/*

=========================================
---------------Sudoku Validator-------------
=========================================


Author:  Subhajit Samanta

Started On:  16/07/2022

Objective:  Take a sudoku puzzle as input and outputs its solution

*/




#include <iostream>
#include <fstream>
using namespace std;

/*Class which provides a data structure to store the sudoku puzzle 
and which also provides different methods to solve the puzzle*/
class validate
{
    int grid[9][9];// A 9x9 matrix to store the sudoku puzzle

public:

/*
@desc:  This default constructor first call the menu and store
        the data in the matrix, then if solution is possible it outputs
        the solution otherwise outputs "No solution exists".

@parm:  None.

@return: None.

*/
    validate()
    {
        menu();
        if (solveSudoku() == true){
            cout<<"\n It's a valid sudoku."<<endl;
        }
            
        else
            cout << "It's a invalid sudoku.";
    }

/*
@desc:  Displays a menu to the user which is basically at the 
        start of the program to display all possible options
	  	from the user.

@parm:  None.

@return: None.

*/
private:
    void menu()
    {

        cout << "\n======================\n";
        cout << "    Sudoku Solver\n";
        cout << "======================\n\n";

        cout << "Welcome to Sudoku Solver!\n";
        cout << "Before we start, you will have to input the puzzle into this program.\n\n";
        cout << "You can either:-\n";
        cout << "\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
        cout << "\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
        cout << "\t   The file must not have a name > 20 characters.\n";
        cout << "\t   The file must be in the same directory as this C++ file.\n";
        cout << "\t   The file must have all 81 values seperated with spaces.\n";
        cout << "\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
        cout << "\t   --> ";

        int option;
        cin >> option;

        if (option == 1)
            readFrameValues();
        else if (option == 2)
            readFrameValuesFile();
        else
        {
            while (true)
            {
                cout << "\nYou seem to have entered an invalid option. Try again.\n";
                cout << "\t   --> ";
                cin >> option;

                if (option == 1)
                    readFrameValues();
                else if (option == 2)
                    readFrameValuesFile();
                else
                    continue;

                break;
            }
        }
    }


/*
@desc:  Reads the values for the Sudoku Frame cell-by-cell.

@parm:  None.

@return: None.

*/

private:
    void readFrameValues()
    {
        cout << "\nEnter the specified value when prompted.\n";
        cout << "Enter 0 if cell is empty.\n\n";

        int rowIter, colIter;

        for (rowIter = 0; rowIter < 9; rowIter++)
        { // Iterating over cells to read vals.
            for (colIter = 0; colIter < 9; colIter++)
            {
                int enteredValue;

                cout << "Enter value for cell[" << rowIter + 1 << "][" << colIter + 1 << "] --> ";
                cin >> enteredValue;

                if (!(enteredValue >= 0 && enteredValue <= 9))
                { // Checking for bounds in input.
                    while (true)
                    { // We loop until valid input is read from user.
                        cout << "Oops! You seem to have entered a wrong value! Try again.\n";
                        cout << "Enter value for cell [" << rowIter + 1 << "][" << colIter + 1 << "] --> ";
                        cin >> enteredValue;

                        if (enteredValue >= 0 && enteredValue <= 9)
                            break;
                    }
                }

                grid[rowIter][colIter] = enteredValue;
            }
            cout << "-------\n"; // Display a break after every row for convenience.
        }
    }


/*
@desc:  Reads the values from a file containing 
        the frame values seperated by whitespaces.

@parm:  None.

@return: None.

*/
private:
    void readFrameValuesFile()
    {

        char filename[30]; // Getting filename.

        cout << "\nEnter the name of the file that contains the Sudoku Puzzle.\n";
        cout << "\t   --> ";
        cin >> filename;

        ifstream sudokuFile; // Opening file for reading.
        sudokuFile.open(filename, ios::in);

        int rowIter, colIter;

        for (rowIter = 0; rowIter < 9; rowIter++)
        { // Iterating over file values.
            for (colIter = 0; colIter < 9; colIter++)
            {
                int readValue;

                sudokuFile >> readValue;

                if (!(readValue >= 0 && readValue <= 9))
                { // Checking bounds for input.
                    cout << "\nValue " << ((rowIter * 9) + colIter + 1) << " in " << filename;
                    cout << " seems to be wrong! Correct the value and try again!\n";
                    exit(EXIT_FAILURE);
                }

                grid[rowIter][colIter] = readValue;

                if (sudokuFile.eof())
                    break; // Breaking if EOF is reached.
            }
        }

        // Gotta have a line which lets us check the frame for any errors

        sudokuFile.close();
    }


/*
@desc:  Checks whether the number is present 
        in the column or not.

@parm:  1. (int)col-- The column of the matrix where we have to check
        2. (int)num-- The number whose presence we have to check

@return: (bool)  whether the value is present in column or not.

*/
    bool isPresentInCol(int col, int num)
    { // check whether num is present in col or not
        for (int rowIter = 0; rowIter < 9; rowIter++)
            if (grid[rowIter][col] == num)
                return true;
        return false;
    }


    /*
@desc:  Checks whether the number is present 
        in the row or not.

@parm:  1. (int)row-- The row of the matrix where we have to check
        2. (int)num-- The number whose presence we have to check

@return: (bool)  whether the value is present in the row or not.

*/
    bool isPresentInRow(int row, int num)
    { // check whether num is present in row or not
        for (int colIter = 0; colIter < 9; colIter++)
            if (grid[row][colIter] == num)
                return true;
        return false;
    }

/*
@desc:  Checks whether the number is present 
        in the 3x3 grid or not.

@parm:  1. (int)boxRow-- The row of the matrix from where the box is starting
        2. (int)boxCol-- The column of the matrix from where the box is starting
        3. (int)num-- The number whose presence we have to check

@return: (bool)  whether the value is present in 3x3 grid or not.

*/
    bool isPresentInBox(int boxRow, int boxCol, int num)
    {
        // check whether num is present in 3x3 box or not
        for (int rowIter = 0; rowIter < 3; rowIter++)
            for (int colIter = 0; colIter < 3; colIter++)
                if (grid[rowIter + boxRow][colIter + boxCol] == num)
                    return true;
        return false;
    }


/*
@desc:  Checks whether the place is empty or not.

@parm:  1. (int &)row-- The row of the matrix
        2. (int &)col-- The column of the matrix 

@return: (bool)  whether the place is empty or not.

*/
    bool findEmptyPlace(int &row, int &col)
    { // get empty location and update row and column
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (grid[row][col] == 0) // marked with 0 is empty
                    return true;
        return false;
    }

/*
@desc:  Checks whether the number is valid in the cell or not.

@parm:  1. (int)row-- The row of the matrix.
        2. (int)col-- The column of the matrix.
        3. (int)num-- The number whose validity we have to check

@return: (bool)  whether the number is valid in the cell or not.

*/
    bool isValidPlace(int row, int col, int num)
    {
        // when item not found in col, row and current 3x3 grid
        return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3, col - col % 3, num);
    }

/*
@desc:  The recursive function which does all the work, 
        this iterates over the possible values for the 
        specified cell one-by-one. Once a value has been filled,
        it goes to the next cell. Here, the same thing happens. 
        If none of the possible values work out, then the function 
        backtracks to the previous cell..

@parm:  None.

@return: (bool)  whether the puzzle is solved or not.

*/
    bool solveSudoku()
    {
        int rowIter, colIter;
        if (!findEmptyPlace(rowIter, colIter))
            return true; // when all places are filled
        for (int num = 1; num <= 9; num++)
        { 
            // valid numbers are 1 - 9
            if (isValidPlace(rowIter, colIter, num))
            { 
                // check validation, if yes, put the number in the grid
                grid[rowIter][colIter] = num;
                if (solveSudoku()) // recursively search for other empty cells in the grid
                    return true;
                grid[rowIter][colIter ] = 0; // backtracking
            }
        }
        return false;
    }
};

int main()
{
    validate s;
    return 0;
}