#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
using namespace std;

#define DEBUG true

class FunctionPair
{
public:
    int LeftFunction;
    int RightFunction;
    int support;
    float confidence;

    FunctionPair() : LeftFunction(0), RightFunction(0), support(0), confidence(-1) {}

    /*
        FunctionPair() : a(0), b(0), support(0), confidence(-1) {}
        is equivalent to:
        FunctionPair() {
            a = 0;
            b = 0;
            support = 0;
            confidence = -1;
        }
    */
};

// global variables
vector<string> callgraph_tokens; // tokenize the callgraph, use to store the callgraph
map<int, string> IDtoFunc; // to store the function ID to function name mapping f(ID) = name
map<string, int> FunctoID; // to store the function name to function ID mapping f(name) = ID
map<int, vector<int>> FuncCalls; // to store the function calls, f(ID) = vector of function IDs
int maxID; // to store the maximum function ID

string retFunctionName(const string &token)
{
    unsigned first, last;
    first = token.find_first_of("\'") + 1;
    last = token.find_last_of("\'");

    return token.substr(first, last - first);
} 

//*
void extract()
{
    // initialize some parameters
    int ID = -1; // to store the function ID
    int i; // to iterate through the callgraph tokens
    string func, TopLevelFunc = "";

    // ignore unnecessary lines
    for (i = 1; i < callgraph_tokens.size(); i++)
    {
        if (callgraph_tokens[i] == "")
        {
            i++;
            break;
        } //
    } //

    // ID assignment to functions
    // Iterate through the callgraph tokens and retrieve all the functions that are being called
    // once retrieved assign them a unique ID to avoid doing string comparison
    for (; i < callgraph_tokens.size(); i++)
    {
        // ignore empty lines
        if (callgraph_tokens[i] == "")
        {
            continue;
        }

        // check if the line contains a function call
        if (callgraph_tokens[i].find("function:") != string::npos ||
            callgraph_tokens[i].find("function") != string::npos)
        {

            func = retFunctionName(callgraph_tokens[i]);
            if (FunctoID.find(func) == FunctoID.end())
            {
                ID++;
                FunctoID[func] = ID;
                IDtoFunc[ID] = func;
            } 
        } 

        // check if the line contains a function call
        // if it does, assign the function name to TopLevelFunc
        // else, assign the function name to func
        // and add the function ID to the FuncCalls map
        if (callgraph_tokens[i].find("function:") != string::npos)
        {
            TopLevelFunc = retFunctionName(callgraph_tokens[i]);
        }
        else if (callgraph_tokens[i].find("function") != string::npos)
        {

            func = retFunctionName(callgraph_tokens[i]);

            // check if the function ID is already in the FuncCalls map
            // if it is, check if the function ID is already in the vector
            // if it is not, add it to the vector
            if (FuncCalls.find(FunctoID[TopLevelFunc]) != FuncCalls.end())
            {
                // check if the function ID is already in the vector
                // if it is not, add it to the vector
                // else, add it to the vector
                if (find(FuncCalls[FunctoID[TopLevelFunc]].begin(),
                         FuncCalls[FunctoID[TopLevelFunc]].end(),
                         FunctoID[func]) == FuncCalls[FunctoID[TopLevelFunc]].end())
                {
                    FuncCalls[FunctoID[TopLevelFunc]].push_back(FunctoID[func]);
                }
            }
            else
            {
                FuncCalls[FunctoID[TopLevelFunc]].push_back(FunctoID[func]);
            }
        }
    }
    maxID = ID;
}

void printBitcode(vector<string> &callgraph_tokens)
{
    cout << "original bitcode :" << endl;
    for (int i = 0; i < callgraph_tokens.size(); i++)
    {
        cout << callgraph_tokens[i] << endl;
    }
}

void printFuntionMapping(map<int, string> &IDtoFunc)
{
    cout << "function map :" << endl;
    for (map<int, string>::iterator it = IDtoFunc.begin(); it != IDtoFunc.end(); ++it)
    {
        cout << it->first << " -> " << it->second << '\n';
    }
}

void printCallFunctions(map<int, vector<int>> &FuncCalls)
{
    cout << endl
         << "call functions :" << endl;
    for (map<int, vector<int>>::iterator it = FuncCalls.begin(); it != FuncCalls.end(); ++it)
    {
        cout << it->first << " calls: ";
        for (int it2 = 0; it2 < it->second.size(); it2++)
        {
            cout << it->second[it2] << " ";
        }
        cout << endl;
    }
}

void inputCallgraph(vector<string> &callgraph_tokens)
{
    string token = ""; // to store each line of input
    while (getline(cin, token))
    {                                      // read each line from standard input - stdin
        callgraph_tokens.push_back(token); // add non-empty lines to the vector
    }
}

int main(int argc, char *argv[])
{
    // read the callgraph from standard input
    // and store it in the callgraph_tokens vector
    inputCallgraph(callgraph_tokens);

    // Parse the call graph
    extract();

#if DEBUG
    // print the original bitcode
    printBitcode(callgraph_tokens);

    // print the function map
    printFuntionMapping(IDtoFunc);

    // print the call functions
    printCallFunctions(FuncCalls);
#endif
}