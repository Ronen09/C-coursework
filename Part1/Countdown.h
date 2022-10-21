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
    }
    return ' ';
}

void getPermutations(vector<string> &permutation,int curIndex,vector<vector<string>> &permutation_list){
                string operatorBank[] = {"+","-","*","/","_"};
                if(curIndex == 5){
                    permutation_list.push_back(permutation);
                } 
                for(int i = 0; i < sizeof(operatorBank); i++){
                permutation[curIndex] = operatorBank[i];
                getPermutations(permutation,
                    curIndex+1,permutation_list);
            }
}

string solver(vector<int>numbers,vector<string> operations)
{   
    string solution = "";
    int k = 0;
    int j = 0;
    for(int i = 0;i<11;i++)
    {
        if(i < 2)
        {
            solution = solution + " " + intToString(numbers[k]);
            k++;
        }
        else if (i % 2 == 0)
        {   
            if(getOpr(j) == '_')
            {   
                solution.pop_back();
                return solution;
            }
            solution = solution + " " + operations[j];
            j++;
        }
        else
        {
            solution = solution + " " + intToString(numbers[k]);
            k++;
        }
    }
    return solution;
}
CountdownSolution solveCountdownProblem(vector<int> numbers,int target)
{   
    vector<string> operation_permutation;
    string solution = "";
    string best_solution = "";
    int best_value = 0;
    int value = 0;
    vector<vector<string>> permutation_list;
    getPermutations(operation_permutation,0,permutation_list);
    for(int i = 0;i<sizeof(permutation_list);i++)
    {   
        operation_permutation = permutation_list[i];
        solution = solver(numbers,operation_permutation);
        value = evaluateCountdown(solution);
        if(target-value < target-best_value)
        {
            best_solution = solution;
            best_value = value;
        }
        else if(target == value)
        {
            return CountdownSolution(solution,value);
        }
        std::next_permutation(numbers.begin(),numbers.end());
    }
    return CountdownSolution(best_solution,best_value);
}


// Do not edit below this line


#endif
