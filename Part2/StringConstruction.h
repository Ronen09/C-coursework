#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;


// TODO: your code goes here:
#include <iostream>
#include <vector>

using namespace std;

int stringConstruction(string target, int copycost, int appendcost)
{
    int result = 0;
    int firstWordsize;
    int secondWordsize;
    int size = target.length();
    string firstWord = target.substr(0,size/2);
    string secondWord = target.substr(size/2, size-size/2);

    while(firstWord.length() > 1)
    {
        while(secondWord.length() > 1)
        {
            if(firstWord.find(secondWord) != std::string::npos)
            {
                if(copycost < appendcost *secondWord.length())
                {
                    result = result + copycost;
                    secondWord = "";
                }

                else
                {
                    result = result + appendcost * secondWord.length();
                    secondWord = "";
                }
            }


            else
            {
                firstWord = firstWord + secondWord[0];
                secondWordsize = secondWord.length();
                secondWord = secondWord.substr(1,secondWordsize-1);

            }
        }

        if(secondWord.length() == 1)
        {
            if(copycost<appendcost)
            {
                if(firstWord.find(secondWord) != std::string::npos)
                {
                    result = result + copycost;
                    firstWordsize = firstWord.length();
                    firstWord = firstWord.substr(0, firstWordsize/2);
                    secondWord = target.substr(firstWordsize/2, firstWordsize - firstWordsize/2);
                }
                
                else
                {
                    result = result + appendcost;
                    firstWordsize = firstWord.length();
                    firstWord = firstWord.substr(0, firstWordsize/2);
                    secondWord = target.substr(firstWordsize/2, firstWordsize - firstWordsize/2);
                }
            }

            else
            {
                result = result + appendcost;
                firstWordsize = firstWord.length();
                firstWord = firstWord.substr(0, firstWordsize/2);
                secondWord = target.substr(firstWordsize/2, firstWordsize - firstWordsize/2);
            }

        }

        else
        {
            firstWordsize = firstWord.length();
            firstWord = firstWord.substr(0, firstWordsize/2);
            secondWord = target.substr(firstWordsize/2, firstWordsize - firstWordsize/2);
        }

    }
    if(firstWord.length() == 1 && secondWord.length() == 1)
    {
        result = result + appendcost + appendcost;
    }

    if(firstWord.length() == 1 && secondWord.length() == 0)
    {
        result = result + appendcost;
    }
    if(firstWord.length() == 1 && secondWord.length() == 2)
    {
        result = result + appendcost*3;
    }

    return result;

}




// do not write or edit anything below this line

#endif