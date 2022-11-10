#ifndef COUNTDOWN_H
#define COUNTDOWN_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;

public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:
vector<string> split(string &str)
{   
    str = str + " ";
    vector<string> words{};
    size_t pos = 0;
    while ((pos = str.find(" ")) != string::npos) {
        words.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    return words;
}
double evaluateCountdown(string s)
{   
    vector<string> output;
    output = split(s);
    vector<double> stack;
    int new_num  = 0;
    int a = 0;
    int b = 0;
    for(int i = 0;i<output.size();i++)
    {   
        if(output[i] == "+")
        {
            if(stack.size() >= 2)
            {   
                a = stack[stack.size() - 1];
                stack.pop_back();
                b = stack[stack.size() - 1];
                stack.pop_back();
                new_num = b+a;
                stack.push_back(new_num);
            }
        }
        else if(output[i] == "-")
        {
            if(stack.size() >= 2)
            {
                a = stack[stack.size() - 1];
                stack.pop_back();
                b = stack[stack.size() - 1];
                stack.pop_back();
                new_num = b-a;
                stack.push_back(new_num);
            }
        }
        else if(output[i] == "*")
        {
            if(stack.size() >= 2)
            {
                a = stack[stack.size() - 1];
                stack.pop_back();
                b = stack[stack.size() - 1];
                stack.pop_back();
                new_num = b*a;
                stack.push_back(new_num);
            }
        }
        else if (output[i] == "/")
        {
            if(stack.size() >= 2)
            {
                a = stack[stack.size() - 1];
                stack.pop_back();
                b = stack[stack.size() - 1];
                stack.pop_back();
                if(a == 0)
                {
                    stack.push_back(0);
                    continue;
                }
                new_num = b/a;
                stack.push_back(new_num);
            }
        }
        else if(output[i] == "")
        {
            continue;
        }
        else
        {
            stack.push_back(std::stod(output[i]));
        }
    }
    if(stack.empty())
    {
        return 0.0;
    }
    int num =  stack[0];
    return num;
}
char getOpr(int i)
{
    switch(i)
    {
        case 0:
            return '+';
        case 1:
            return '-';
        case 2:
            return '*';
        case 3:
            return '/';
        case 4:
            return '_';
    }
    return ' ';
}
vector<vector<int>> getNumberPermutations(vector<int> &numbers)
{
    vector<vector<int>> permutations;
    for(int i = 0;i<numbers.size();i++)
    {   
        for(int j = 0;j<numbers.size();j++)
        {   
            if(i == j)
            {
                continue;
            }
            for(int k = 0;k<numbers.size();k++)
            {   
                if(k == i || k == j)
                {
                    continue;
                }
                for(int l = 0;l<numbers.size();l++)
                {   
                    if(l == i || l == j || l == k)
                    {
                        continue;
                    }
                    for(int m = 0;m<numbers.size();m++)
                    {   
                        if(m == i || m == j || m == k || m == l)
                        {
                            continue;
                        }
                        for(int n = 0;n<numbers.size();n++)
                        {   
                            if(n == i || n == j || n == k || n == l || n == m)
                            {
                                continue;
                            }
                            else
                            {
                                vector<int> permutation;
                                permutation.push_back(numbers[i]);
                                permutation.push_back(numbers[j]);
                                permutation.push_back(numbers[k]);
                                permutation.push_back(numbers[l]);
                                permutation.push_back(numbers[m]);
                                permutation.push_back(numbers[n]);
                                permutations.push_back(permutation);
                            }
                        }
                    }
                }
            }
        }
    }
    return permutations;
}
CountdownSolution solveCountdownProblem(vector<int> numbers, int targetnum)
{
    string tem;
    double result;
    string algo = "+-*/";
    vector<vector<int>> permutations = getNumberPermutations(numbers);
    for(vector<int> permutation : permutations){
        for(int a = 0; a < 4; a++)
        {
            for(int b = 0; b < 4; b++)
            {
                tem = intToString(permutation[0])+ " " + intToString(permutation[1]) + " " + intToString(permutation[2]) + " " + algo[a] + " " + algo[b] ;
                result = evaluateCountdown(tem);
                if(result == targetnum)
                {
                    cout<<tem<<endl;
                    return CountdownSolution(tem, result);
                }
            }
        }
    }
    for(vector<int> permutation : permutations){
        for(int a = 0; a < 4; a++)
        {
            for(int b = 0; b < 4; b++)
            {
                for(int c = 0; c < 4; c++)
                {
                            tem = intToString(permutation[0])+ " " + intToString(permutation[1]) + " " + intToString(permutation[2]) + " " + intToString(permutation[3]) + " " + algo[a] + " " + algo[b] + " " + algo[c];
                            result = evaluateCountdown(tem);
                            if(result == targetnum)
                            {
                                cout<<tem<<endl;
                                return CountdownSolution(tem, result);
                            }
                }
            }
        }
    }

    for(vector<int> permutation : permutations){
        for(int a = 0; a < 4; a++)
        {
            for(int b = 0; b < 4; b++)
            {
                for(int c = 0; c < 4; c++)
                {
                    for(int d = 0; d < 4; d++)
                    {
                            tem = intToString(permutation[0])+ " " + intToString(permutation[1]) + " " + intToString(permutation[2]) + " " + intToString(permutation[3]) + " " + intToString(permutation[4]) + " " + algo[a] + " " + algo[b] + " " + algo[c] + " " + algo[d];
                            result = evaluateCountdown(tem);
                            if(result == targetnum)
                            {
                                cout<<tem<<endl;
                                return CountdownSolution(tem, result);
                            }
                    }
                }
            }
        }
    }

    for(vector<int> permutation : permutations){
        for(int a = 0; a < 4; a++)
        {
            for(int b = 0; b < 4; b++)
            {
                for(int c = 0; c < 4; c++)
                {
                    for(int d = 0; d < 4; d++)
                    {
                        for(int e = 0; e < 4; e++)
                        {
                            tem = intToString(permutation[0])+ " " + intToString(permutation[1]) + " " + intToString(permutation[2]) + " " + intToString(permutation[3]) + " " + intToString(permutation[4]) + " " + intToString(permutation[5]) + " " + algo[a] + " " + algo[b] + " " + algo[c] + " " + algo[d] + " " + algo[e];
                            result = evaluateCountdown(tem);
                            if(result == targetnum)
                            {
                                cout<<tem<<endl;
                                return CountdownSolution(tem, result);
                            }
                        }
                    }
                }
            }
        }
    }

    return CountdownSolution(tem, result);
}


// Do not edit below this line


#endif
