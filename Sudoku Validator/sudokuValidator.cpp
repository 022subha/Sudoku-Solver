/*

=========================================
---------------Sudoku Validator-------------
=========================================


Author:  Subhajit Samanta

Started On:  16/06/2022

Objective:  Take a sudoku puzzle as input and outputs its solution

*/

#include <iostream>
#include <fstream>
using namespace std;

/*Class which provides a data structure to store the sudoku puzzle
and which also provides different methods to solve the puzzle*/
class validate
{
    int grid[9][9]; // A 9x9 matrix to store the sudoku puzzle

public:
    /*
    @desc:  This default constructor first call the menu and store
            the data in the matrix, then it validates the matrix as a sudoku".

    @parm:  None.

    @return: None.

    */
    validate()
    {
        menu();
        validateFrame();
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


                grid[rowIter][colIter] = readValue;

                if (sudokuFile.eof())
                    break; // Breaking if EOF is reached.
            }
        }

        // Gotta have a line which lets us check the frame for any errors

        sudokuFile.close();
    }




    /*
    @desc:  Calls functions which validates the rows, 
            columns and 3x3 grids.

    @parm:  None.

    @return: None.

    */
    void validateFrame()
    {
        if (valuesAreValid())
        {
            if (rowsAreValid())
            {
                if (columnsAreValid())
                {
                    if (ThreeByThreeSquaresAreValid())
                    {
                        cout << "\nYour puzzle is valid!\n\n";
                    }
                    else
                        cout << "Your puzzle in invalid!\n";
                }
                else
                    cout << "Your puzzle is invalid!\n";
            }
            else
                cout << "Your puzzle is invalid!\n";
        }
        else
            cout << "Your puzzle is invalid!\n";
    }


    /*
    @desc:  Checks if all values in the grid
            are between the ranges of 1-9.

    @parm:  None.

    @return: None.

    */
    bool valuesAreValid()
    {
        int rowIter, colIter;

        for (rowIter = 0; rowIter < 9; rowIter++)
        {
            for (colIter = 0; colIter < 9; colIter++)
            {
                int cellValue = grid[rowIter][colIter];
                if (!(cellValue >= 0 && cellValue <= 9))
                    return false;
            }
        }

        return true;
    }

    /*
    @desc:  Checks if the columns in the grid are valid.

    @parm:  None.

    @return: (bool) Whether the columns are valid or not.

    */
    bool columnsAreValid()
    {

        int rowIter, colIter, valIter;

        for (colIter = 0; colIter < 9; colIter++)
        { // Iterating over cols

            for (valIter = 1; valIter <= 9; valIter++)
            { // Iter over 1-9

                if (columnContains(colIter, valIter) == false)
                    return false;

            } // Value iteration loops ends

        } // Col iteration loop ends here

        return true;
    }


    /*
    @desc:  Checks if the rows in the grid are valid.

    @parm:  None.

    @return: (bool) Whether the rows are valid or not.

    */
    bool rowsAreValid()
    { // check whether num is present in row or not
        for (int rowIter = 0; rowIter < 9; rowIter++)
        {
            for (int valIter = 1; valIter <= 9; valIter++)
            {
                if (rowContains(rowIter, valIter) == false)
                    return false;
            }
        }
        return true;
    }


    /*
    @desc:  Checks if the 3x3 boxes in the grid are valid.

    @parm:  None.

    @return: (bool) Whether the 3x3 boxes are valid or not.

    */
    bool ThreeByThreeSquaresAreValid()
    {

        int squareIter, valIter;

        for (squareIter = 0; squareIter < 9; squareIter++)
        { // Iter over squares

            for (valIter = 1; valIter <= 9; valIter++)
            { // Iter over 1-9

                if (squareContains(squareIter, valIter) == false)
                    return false;

            } // Value iteration loop ends here

        } // Square iteration loop ends here

        return true;
    }


    /*
    @desc:  Checks whether a given value 
            is present in a specified column.

    @parm:  1. (int)col-- The column of the matrix where we have to check
            2. (int)value-- The number whose presence we have to check

    @return: (bool)  whether the value is present in the column or not.

    */
    bool columnContains(int col, int value)
    {
        int rowIter = 0;
        for (rowIter = 0; rowIter < 9; rowIter++)
        {
            if (grid[rowIter][col] == value)
                return true;
        }
        return false;
    }

    /*
    @desc:  Checks whether a given value 
            is present in a specified row.

    @parm:  1. (int)row-- The row of the matrix where we have to check
            2. (int)value-- The number whose presence we have to check

    @return: (bool)  whether the value is present in the row or not.

    */

private:
    bool rowContains(int row, int value)
    {
        int colIter;
        for (colIter = 0; colIter < 9; colIter++)
        {
            if (grid[row][colIter] == value)
                return true;
        }
        return false;
    }



    /*
    @desc:  Checks whether the number is present
            in the 3x3 grid or not.

    @parm:  1. (int)squareNumber-- The 3x3 grid no.
            2. (int)value-- The number whose presence we have to check

    @return: (bool)  whether the value is present in 3x3 grid or not.

    */
    bool squareContains(int squareNumber, int value)
    {
        int rowStart = (squareNumber / 3) * 3;
        int rowEnd = rowStart + 2;

        int colStart = (squareNumber % 3) * 3;
        int colEnd = colStart + 2;

        int rowIter, colIter;
        for (rowIter = rowStart; rowIter <= rowEnd; rowIter++)
        {
            for (colIter = colStart; colIter <= colEnd; colIter++)
            {
                if (grid[rowIter][colIter] == value)
                    return true;
            }
        }

        return false;
    }



    /*
    @desc:  Checks whether the number is valid in the cell or not.

    @parm:  1. (int)row-- The row of the matrix.
            2. (int)col-- The column of the matrix.
            3. (int)num-- The number whose validity we have to check

    @return: (bool)  whether the number is valid in the cell or not.

    */
};

int main()
{
    validate s;
    return 0;
}
