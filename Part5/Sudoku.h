#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include <memory>
using std::unique_ptr;

using std::vector;
using std::set;
using std::cout;
using std::endl;

// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable
{

private:
    vector<vector<set<int>>> solution;


public:

    Sudoku(const int &size)
    {
        for (int i = 0; i < size; ++i)
        {
            vector<set<int>> temp;
            for (int j = 0; j < size; ++j)
            {
                set<int> x;
                for (int k = 1; k <= size; ++k)
                {
                    x.insert(k);
                }
                temp.push_back(x);
            }
            solution.push_back(temp);
        }
    }

    Sudoku(const Sudoku &other)
    {
        solution= other.solution;
    }

    int getSquare(int row, int col) const
    {
        if (solution[row][col].size() == 1)
        {
            return *solution[row][col].begin();
        } else
        {
            return -1;
        }

    }

    bool setSquare(int row, int col, int value)
    {
        solution[row][col].clear();
        solution[row][col].insert(value);

        //each box in the grid e.g 9x9 by grid has 9 3x3 boxes
        int subGridSize = sqrt(solution.size());
        int finalGridSize =0;
        int gridSize;
        bool search = true;
        vector<vector<set<int>>> tempGrid =solution;
        while(search)
        {
            gridSize=0;

            for (int row = 0; row < solution.size(); ++row)
            {
                for (int col = 0; col < solution.size(); ++col)
                {
                    gridSize+=solution[row][col].size();
                    if (solution[row][col].size() == 1)
                    {
                        int aValue = getSquare(row, col);
                        for (int i = 0; i < solution.size(); ++i)
                        {
                            if (i!=col) {
                                solution[row][i].erase(aValue);
                            }
                            if (i!=row) {
                                solution[i][col].erase(aValue);
                            }
                        }
                        int subGridStartRow = (row - (row % subGridSize));
                        int subGridStartCol = (col - (col % subGridSize));

                        int subGridEndRow = subGridStartRow + (subGridSize - 1);
                        int subGridEndCol = subGridStartCol + (subGridSize - 1);

                        for (int tempRow = subGridStartRow; tempRow <= subGridEndRow; ++tempRow)
                        {
                            for (int tempCol = subGridStartCol; tempCol <= subGridEndCol; ++tempCol)
                            {
                                if (row != tempRow && col != tempCol)
                                {
                                    solution[tempRow][tempCol].erase(aValue);
                                }
                            }
                        }
                    }
                    else if(solution[row][col].size()==2)
                    {
                        set<int> doNotDelete = solution[row][col];
                        vector<int> values;
                        for(auto &e: solution[row][col])
                        {
                            values.push_back(e);
                        }

                        int subGridStartRow = (row - (row % subGridSize));
                        int subGridStartCol = (col - (col % subGridSize));

                        int subGridEndRow = subGridStartRow + (subGridSize - 1);
                        int subGridEndCol = subGridStartCol + (subGridSize - 1);

                        int rowCheck = 0;
                        int colCheck = 0;
                        int gridCheck = 0;

                        for(int i=0; i<solution.size(); ++i)
                        {
                            if(doNotDelete==solution[row][i])
                            {
                                rowCheck++;
                            }
                            if(doNotDelete==solution[i][col])
                            {
                                colCheck++;
                            }
                        }
                        for (int tempRow = subGridStartRow; tempRow <= subGridEndRow; ++tempRow)
                        {
                            for (int tempCol = subGridStartCol; tempCol <= subGridEndCol; ++tempCol)
                            {
                                if (doNotDelete==solution[tempRow][tempCol])
                                {
                                    gridCheck++;
                                }
                            }
                        }
                        for(int i=0; i<solution.size(); ++i)
                        {
                            if(doNotDelete!=solution[row][i] && rowCheck==2)
                            {
                                solution[row][i].erase(values[0]);
                                solution[row][i].erase(values[1]);
                            }
                            if(doNotDelete!=solution[i][col] && colCheck==2)
                            {
                                solution[i][col].erase(values[0]);
                                solution[i][col].erase(values[1]);
                            }
                        }


                        for (int tempRow = subGridStartRow; tempRow <= subGridEndRow; ++tempRow)
                        {
                            for (int tempCol = subGridStartCol; tempCol <= subGridEndCol; ++tempCol)
                            {
                                if (doNotDelete!=solution[tempRow][tempCol] && gridCheck==2) 
                                {
                                    solution[tempRow][tempCol].erase(values[0]);
                                    solution[tempRow][tempCol].erase(values[1]);
                                }
                            }
                        }

                    }
                    else if(solution[row][col].size() ==3)
                    {
                        set<int> doNotDelete = solution[row][col];
                        vector<int> values;
                        for(auto &e: solution[row][col]){
                            values.push_back(e);
                        }

                        int subGridStartRow = (row - (row % subGridSize));
                        int subGridStartCol = (col - (col % subGridSize));

                        int subGridEndRow = subGridStartRow + (subGridSize - 1);
                        int subGridEndCol = subGridStartCol + (subGridSize - 1);

                        int rowCheck = 0;
                        int colCheck = 0;
                        int gridCheck = 0;

                        for(int i=0; i<solution.size(); ++i)
                        {
                            if(doNotDelete==solution[row][i])
                            {
                                rowCheck++;
                            }
                            if(doNotDelete==solution[i][col])
                            {
                                colCheck++;
                            }
                        }

                        for (int tempRow = subGridStartRow; tempRow <= subGridEndRow; ++tempRow)
                        {
                            for (int tempCol = subGridStartCol; tempCol <= subGridEndCol; ++tempCol)
                            {
                                if (doNotDelete==solution[tempRow][tempCol])
                                {
                                    gridCheck++;
                                }
                            }
                        }

                        for(int i=0; i<solution.size(); ++i){
                            if(doNotDelete!=solution[row][i] && rowCheck==3)
                            {
                                solution[row][i].erase(values[0]);
                                solution[row][i].erase(values[1]);
                            }
                            if(doNotDelete!=solution[i][col] && colCheck==3)
                            {
                                solution[i][col].erase(values[0]);
                                solution[i][col].erase(values[1]);
                            }
                        }


                        for (int tempRow = subGridStartRow; tempRow <= subGridEndRow; ++tempRow)
                        {
                            for (int tempCol = subGridStartCol; tempCol <= subGridEndCol; ++tempCol)
                            {
                                if (doNotDelete!=solution[tempRow][tempCol] && gridCheck==3) {
                                    solution[tempRow][tempCol].erase(values[0]);
                                    solution[tempRow][tempCol].erase(values[1]);
                                }
                            }
                        }
                    }
                    else if (solution[row][col].size()==0)
                    {
                        solution=tempGrid;
                        return 0;
                    }
                }
            }
            if (gridSize == finalGridSize)
            {
                search=false;
            }else
            {
                finalGridSize =gridSize;
            }
        }
        return true;
    }

    bool isSolution() const
    {
        for (int i = 0; i < solution.size(); ++i)
        {
            for (int j = 0; j < solution.size(); ++j)
            {
                if(getSquare(i,j)==-1)
                {
                    return 0;
                }
            }
        }
        return 1;
    }

    void write(ostream & output) const
    {
        int gridSize = (int)sqrt(solution.size());
        for (int i = 0; i < solution.size(); i++)
        {
            for (int j = 0; j < solution.size(); j++)
            {
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
        vector<unique_ptr<Searchable>> successors;
        int rowWithMoreThanOneOption = -1;

        //find the first row containing a square with more than one value;
        for (int row=0; row<solution.size();++row)
        {
            for(int col=0; col<solution.size();++col)
            {
                if(getSquare(row,col)==-1)
                {
                    rowWithMoreThanOneOption =row;
                    row = solution.size();
                    col = solution.size();
                }
            }
        }
        int leftMostCol =-1;
        for(int col=0; col<solution.size();col++)
        {
            if(getSquare(rowWithMoreThanOneOption,col)==-1)
            {
                leftMostCol=col;
                col = solution.size();
            }
        }

        set<int> leftMostSetOnRow = solution[rowWithMoreThanOneOption][leftMostCol];


            for (set<int>::iterator x = leftMostSetOnRow.begin(); x != leftMostSetOnRow.end(); ++x)
            {
                unique_ptr<Sudoku> anotherSudokuBoard =unique_ptr<Sudoku>(new Sudoku(*this));
                if(anotherSudokuBoard->setSquare(rowWithMoreThanOneOption,leftMostCol, *x))
                {
                    successors.push_back(std::move(anotherSudokuBoard));
                }

            }

            if (successors.size()==1 && !((*successors.begin())->isSolution()))
            {
                 return successors[0]->successors();
            }
            return successors;


    }

    int heuristicValue() const
    {
        int count =0;
        for(int i=0; i<solution.size();++i)
        {
            for(int j=0; j<solution.size();++j)
            {
              if (getSquare(i,j)==-1)
              {
                ++count;
              }
            }
        }
        return count;
    }

};


#endif
