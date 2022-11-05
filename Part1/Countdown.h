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

CountdownSolution solveCountdownProblem(vector<int> numbers,int target)
{  
    string solution = "";
    int value = 0;
    string best_solution;
    int best_value = 0;
    for(int i = 0;i<numbers.size();i++)
    {   
        solution = "";
        value = 0;
        solution = solution + intToString(numbers[i]) + " ";
        for(int j = 0;j<numbers.size();j++)
        {   
            if(i == j)
            {
                continue;
            }
            solution = solution + intToString(numbers[j]) + " ";
            for(int k = 0;k<5;k++)
            {   
                if(getOpr(k) == '_')
                {
                    continue;
                }
                solution = solution + getOpr(k) + " ";
                if(target == evaluateCountdown(solution))
                {
                    return CountdownSolution(solution,target);
                }
                if(target - evaluateCountdown(solution) < target - best_value)
                {
                    best_solution = solution;
                    best_value = evaluateCountdown(solution);
                }
                for(int l = 0;l<numbers.size();l++)
                {   
                    if(l == i || l == j)
                    {
                        continue;
                    }
                    solution = solution + intToString(numbers[l]) + " ";
                    for(int m = 0;m<5;m++)
                    {   
                        if(getOpr(m) == '_')
                        {
                            continue;
                        }
                        solution = solution + getOpr(m) + " ";
                        if(target == evaluateCountdown(solution))
                        {
                            return CountdownSolution(solution,target);
                        }
                        if(target - evaluateCountdown(solution) < target - best_value)
                        {
                            best_solution = solution;
                            best_value = evaluateCountdown(solution);
                        }
                        for(int n = 0;n<numbers.size();n++)
                        {   
                            if(n == i || n == j || n == l)
                            {
                                continue;
                            }
                            solution = solution + intToString(numbers[n]) + " ";
                            for(int o = 0;o<5;o++)
                            {   
                                if(getOpr(o) == '_')
                                {
                                    continue;
                                }
                                if(target == evaluateCountdown(solution))
                                {
                                    return CountdownSolution(solution,target);
                                }
                                solution = solution + getOpr(o) + " ";
                                if(target - evaluateCountdown(solution) < target - best_value)
                                {
                                    best_solution = solution;
                                    best_value = evaluateCountdown(solution);
                                }
                                for(int p = 0;p<numbers.size();p++)
                                {   
                                    if(p == i || p == j || p == l || p == n)
                                    {
                                        continue;
                                    }
                                    solution = solution + intToString(numbers[p]) + " ";
                                    for(int q = 0;q<5;q++)
                                    {   
                                        if(getOpr(q) == '_')
                                        {
                                            continue;
                                        }
                                        solution = solution + getOpr(q) + " ";
                                        if(target == evaluateCountdown(solution))
                                        {
                                            return CountdownSolution(solution,target);
                                        }
                                        if(target - evaluateCountdown(solution) < target - best_value)
                                        {
                                            best_solution = solution;
                                            best_value = evaluateCountdown(solution);
                                        }
                                        for(int r = 0;r<numbers.size();r++)
                                        {   
                                            if(r == i || r == j || r == l || r == n || r == p)
                                            {
                                                continue;
                                            }
                                            solution = solution + intToString(numbers[r]) + " ";
                                            for(int s = 0;s<5;s++)
                                            {
                                                if(getOpr(s) == '_')
                                                {
                                                    continue;
                                                }
                                                if(target == evaluateCountdown(solution))
                                                {
                                                    return CountdownSolution(solution,target);
                                                }
                                                solution = solution + getOpr(s) + " ";
                                                if(target - evaluateCountdown(solution) < target - best_value)
                                                {
                                                    best_solution = solution;
                                                    best_value = evaluateCountdown(solution);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return CountdownSolution(best_solution, best_value);
}


// Do not edit below this line


#endif
