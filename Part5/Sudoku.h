#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <utility>
#include <math.h>
using std::vector;
using std::set;

// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable {

private:
    int boardSize;
    vector<vector<set<int>>> solution;

public:

    Sudoku(int size): boardSize(size)
    {
        for (int i = 0; i < boardSize; i++)
        {
            vector<set<int> > column;
            for (int j = 0; j < boardSize; j++)
            {
                set<int> possibleSolutions;
                for (int x = 0; x < size; x++)
                {
                    possibleSolutions.insert(x + 1);
                }
                column.push_back(possibleSolutions);
            }
            solution.push_back(column);
        }
    }


    //returns the value within a square on the grid only if it is the only possible option otherwise it returns -1
    int getSquare(int row, int col)
    {

        if (solution[row][col].size() == 1)
        {
            return *solution[row][col].begin();
        }
        else
        {
            return -1;
        }
    }


    //sets the value of a square on the grid and updates the other squares potential numbers
    bool setSquare(int row, int col, int value)
    {
        solution[row][col].clear();
        solution[row][col].insert(value);

        bool isSmaller = true;
        int gridSize = (int)sqrt(boardSize);
        while (isSmaller)
        {

            isSmaller = false;

            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++)
                {
                    if (solution[i][j].size() == 1)
                    {

                        //removes value from rows and columns
                        for (int k = 0; k < boardSize; k++)
                        {
                            for (int l = 0; l < boardSize; l++)
                            {

                                if (i == k ^ j == l){

                                    if (solution[k][l].find(getSquare(i,j)) != solution[k][l].end()){

                                        solution[k][l].erase(getSquare(i,j));
                                        isSmaller = true;

                                    }
                                }

                            }
                        }

                        //removes value from squares in the same box
                        int xPosition = i - (i % gridSize);
                        int yPosition = j - (j % gridSize);

                        for (int x = xPosition; x < (xPosition + gridSize); x++) 
                        {
                            for (int y = yPosition; y < (yPosition + gridSize); y++)
                             {

                                if (solution[x][y].find(getSquare(i,j)) != solution[x][y].end())
                                {
                                    if(x != i || y != j)
                                    {
                                        solution[x][y].erase(getSquare(i,j));
                                        isSmaller = true;
                                    }

                                }

                            }
                        }
                    }

                    if (solution[i][j].empty())
                    {
                        return false;
                    }

                }
            }
        }
        return true;
    }

    bool isSolution() const
    {
        bool onlyOne = true;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (solution[i][j].size() != 1){
                    onlyOne = false;
                }
            }
        }

        return onlyOne;
    }

    void write(ostream & output) const
    {
        int gridSize = (int)sqrt(boardSize);
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if(j % gridSize == 0)
                {
                    output << "|";
                }
                if (solution[i][j].size() == 1)
                {
                    output << *solution[i][j].begin();
                }
                else 
                {
                    output << " ";
                }
            }
            output << "\n";
            if(i % gridSize == 2)
            {
                output << "------------";
                output << "\n";
            }
        }
    }

    vector<unique_ptr<Searchable> > successors() const
    {
        vector<unique_ptr<Searchable> > successors;
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (solution[i][j].size() != 1)
                {
                    for(int x : solution[i][j])
                    {
                        auto* testBoard = new Sudoku(*this);

                        if(testBoard ->setSquare(i,j,x))
                        {
                            successors.push_back(unique_ptr<Searchable>(testBoard));
                        }
                        else
                        {
                             delete testBoard;
                        }
                    }
                    return successors;
                }

            }
        }

    }



};


#endif
