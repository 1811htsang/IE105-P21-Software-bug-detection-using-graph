#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdio>
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
map<int, string> IDtoFunc;       // to store the function ID to function name mapping f(ID) = name
map<string, int> FunctoID;       // to store the function name to function ID mapping f(name) = ID

// global variables for basic total reduction
map<int, vector<int>> FuncCallTotalReduction; // to store the function calls, f(ID) = vector of function IDs
int maxID;                                    // to store the maximum function ID

// global variables for total reduction with edge weight
map<int, map<int, int>> FuncCallTotalReductionWeight; // to store the function calls, f(ID) = vector of function IDs with edge weight
int threshold;                                        // to store the threshold for edge weight

string demangle(const string &mangled_name)
{
    string command = "c++filt -t " + mangled_name;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        return mangled_name; // Trả lại tên gốc nếu popen thất bại
    }
    char buffer[128];
    string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }
    pclose(pipe);
    // Loại bỏ newline nếu có
    if (!result.empty() && result.back() == '\n')
    {
        result.pop_back();
    }
    return result;
}

string retFunctionName(const string &token)
{
    unsigned first, last;
    first = token.find_first_of("\'") + 1;
    last = token.find_last_of("\'");

    return token.substr(first, last - first);
}

//*
void extract_basic_total_reduction()
{
    // initialize some parameters
    int ID = -1; // to store the function ID
    int i;       // to iterate through the callgraph tokens
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
    // split this to a function

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
            if (FuncCallTotalReduction.find(FunctoID[TopLevelFunc]) != FuncCallTotalReduction.end())
            {
                // check if the function ID is already in the vector
                // if it is not, add it to the vector
                // else, add it to the vector
                if (find(FuncCallTotalReduction[FunctoID[TopLevelFunc]].begin(),
                         FuncCallTotalReduction[FunctoID[TopLevelFunc]].end(),
                         FunctoID[func]) == FuncCallTotalReduction[FunctoID[TopLevelFunc]].end())
                {
                    FuncCallTotalReduction[FunctoID[TopLevelFunc]].push_back(FunctoID[func]);
                }
            }
            else
            {
                FuncCallTotalReduction[FunctoID[TopLevelFunc]].push_back(FunctoID[func]);
            }
        }
    }
    maxID = ID;
}

void extract_total_reduction_weight()
{
    // initialize some parameters
    int ID = -1; // to store the function ID
    int i;       // to iterate through the callgraph tokens
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
    // split this to a function

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

            // check if the function ID is already in the mapping
            // if it is, check if the function ID is already in the map
            // if the function ID is already in the map
            // count the number of times it appears and increment the edge weight
            // if it is not, add it to the map and increment the edge weight, in which based edge weight is set to 1

            if (FuncCallTotalReductionWeight.find(FunctoID[TopLevelFunc]) != FuncCallTotalReductionWeight.end())
            {
                // check if the function ID is already in the map
                // if it is, increment the edge weight
                if (FuncCallTotalReductionWeight[FunctoID[TopLevelFunc]].find(FunctoID[func]) != FuncCallTotalReductionWeight[FunctoID[TopLevelFunc]].end())
                {
                    FuncCallTotalReductionWeight[FunctoID[TopLevelFunc]][FunctoID[func]]++;
                }
                else
                {
                    FuncCallTotalReductionWeight[FunctoID[TopLevelFunc]][FunctoID[func]] = 1;
                }
            }
            else
            {
                FuncCallTotalReductionWeight[FunctoID[TopLevelFunc]][FunctoID[func]] = 1;
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
        cout << it->first << " -> " << it->second << " == " << demangle(it->second) << '\n';
    }
}

void printCallFunctions(map<int, vector<int>> &FuncCalls)
{
    cout << endl
         << "call functions with total reduction no edge weight :" << endl;
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

void printCallFunctionsWeight(map<int, map<int, int>> &FuncCalls)
{
    cout << endl
         << "call functions with edge weight :" << endl;
    for (map<int, map<int, int>>::iterator it = FuncCalls.begin(); it != FuncCalls.end(); ++it)
    {
        cout << it->first << " calls: ";
        for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            cout << it2->first << "(" << it2->second << ") ";
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

    // Parse the call graph with simple total reduction
    // and store the function calls in the FuncCalls map
    // and the function ID to function name mapping in the FunctoID map
    // and the function name to function ID mapping in the IDtoFunc map
    // and the maximum function ID in the maxID variable
    extract_basic_total_reduction();

    extract_total_reduction_weight();

#if DEBUG
    // print the original bitcode
    printBitcode(callgraph_tokens);

    // print the function map
    printFuntionMapping(IDtoFunc);

    // print the call functions
    printCallFunctions(FuncCallTotalReduction);

    // print the call functions with edge weight
    printCallFunctionsWeight(FuncCallTotalReductionWeight);
#endif
}