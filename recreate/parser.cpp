/*
	Procedure of the program:
	1. Read the callgraph from standard input
	2. Parse the callgraph to extract function names and their IDs
	3. Transform the callgraph for inter-procedural analysis
	4. Analyze the callgraph to calculate support and confidence for function pairs
	5. Find bugs in the callgraph by checking for missing function pairs
	6. Print the results to standard output
*/

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

class FunctionPair
{
public:
    int a; // represents the first function in the pair
    int b; // represents the second function in the pair
    int support; // represents the number of times the pair occurs together
    float confidence; // represents the confidence level of the pair

    FunctionPair() : a(0), b(0), support(0), confidence(-1) {}

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

#define DEBUG true

int IPC_LEVELS = 1; // default levels of inter-procedural analysis (1 turns it off completely)

// global variables
unsigned int threshhold_support = 5;		 // default support
unsigned int threshhold_confidence = 80;	 // default confidence
vector<string> callgraph_tokens; // tokenize the callgraph
map<int, string> id_to_func;
map<string, int> func_to_id;
map<int, vector<int>> function_call;		 // Modified for inter-procedural analysis
map<int, vector<int>> origin_function_call; // The original function call data structure, corresponding to level 1 inter-procedural analysis
int maxID;
vector<map<int, FunctionPair>> Pairs;

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

string getFuncFromToken(const string &token)
{
	unsigned first, last;
	first = token.find_first_of("\'") + 1;
	last = token.find_last_of("\'");

	return token.substr(first, last - first);
} // getFuncFromToken

void parser()
{
	// initialize some parameters
	int ID = -1;
	int i;
	string func, TopLevelFunc = "";

	// This is to preset the iterator to the lines after the <<null function>> call
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

		// Skip empty lines
		if (callgraph_tokens[i] == "")
		{
			continue;
		}

		// check if the line contains a function call
		if (callgraph_tokens[i].find("function:") != string::npos ||
			callgraph_tokens[i].find("function") != string::npos)
		{

			func = getFuncFromToken(callgraph_tokens[i]);
			if (func_to_id.find(func) == func_to_id.end())
			{
				ID++;
				func_to_id[func] = ID;
				id_to_func[ID] = func;
			} 
		} 

		// check if the line contains a function call
        // if it does, assign the function name to TopLevelFunc
        // else, assign the function name to func
        // and add the function ID to the function_call map
		if (callgraph_tokens[i].find("function:") != string::npos)
		{
			TopLevelFunc = getFuncFromToken(callgraph_tokens[i]);
		} 
		else if (callgraph_tokens[i].find("function") != string::npos)
		{
			func = getFuncFromToken(callgraph_tokens[i]);

			// check if the function ID is already in the function_call map
            // if it is, check if the function ID is already in the vector
            // if it is not, add it to the vector
			if (function_call.find(func_to_id[TopLevelFunc]) != function_call.end())
			{
				// check if the function ID is already in the vector
                // if it is not, add it to the vector
                // else, add it to the vector
				if (find(function_call[func_to_id[TopLevelFunc]].begin(),
						 function_call[func_to_id[TopLevelFunc]].end(),
						 func_to_id[func]) == function_call[func_to_id[TopLevelFunc]].end())
				{
					function_call[func_to_id[TopLevelFunc]].push_back(func_to_id[func]);
				}
			}
			else
			{
				function_call[func_to_id[TopLevelFunc]].push_back(func_to_id[func]);
			}
		}

	}
	maxID = ID;
}

void ipc_transform()
{
	/*
	Transforms the internal function call structure for interprocedural analysis
	Let function_call-K be the graph where each node has an edge to all
	node that could be reached in K steps or less in the original function_call graph
	Formally, replaces the graph in function_call with function_call-IPC_LEVELS
	At each step, the algorithm starts with Oldfunction_call = function_call-i, and finds
	function_call i+i by finding all verticies reachable in i+1 steps.
	*/

	/*
		Better explanation:
		With K is the number of levels of inter-procedural analysis
		function_call-K is the graph where each node has an edge to all
		node that could be reached in K steps or less in the original function_call graph
		Formally, replaces the graph in function_call with function_call-IPC_LEVELS
		At each step, the algorithm starts with Oldfunction_call = function_call-i, and finds
		function_call i+i by finding all verticies reachable in i+1 steps.
		For example, if we have a function A that calls B and C, and B calls D,
		then function_call-1 would be:
		A -> B
		A -> C
		B -> D
		function_call-2 would be:
		A -> B
		A -> C
		A -> D
		B -> D
		function_call-3 would be:
		A -> B
		A -> C
		A -> D
		B -> D
		C -> D

		Hints: with K = 1, we have the original graph so IPC is off
	*/

	// Initialize some parameters
	int a, b;
	map<int, vector<int>> Newfunction_call = function_call;
	map<int, vector<int>> Oldfunction_call = function_call;
	origin_function_call = function_call;

	// Repeatedly find
	for (int i = 1; i < IPC_LEVELS; i++)
	{
		Oldfunction_call = Newfunction_call;
		// Loop through all verticies in the graph
		for (map<int, vector<int>>::iterator i = function_call.begin(); i != function_call.end(); ++i)
		{
			a = i->first;
			vector<int> &v = i->second;
			// Find all verticies reachable in i+1 steps, 
			// find all verticies reachable from this nodes immediate children
			// in the original graph in i steps.
			for (int j = 0; j < v.size(); j++)
			{
				b = v[j];
#if DEBUG
				cout << a << "," << b << endl;
#endif
				// Merge verticies into the vector
				Newfunction_call[a].reserve(Newfunction_call[a].size() + Oldfunction_call[b].size());
				Newfunction_call[a].insert(Newfunction_call[a].end(), Oldfunction_call[b].begin(), Oldfunction_call[b].end());
			}
			// Sort and remove duplicates
			sort(Newfunction_call[a].begin(), Newfunction_call[a].end());
			Newfunction_call[a].erase(unique(Newfunction_call[a].begin(), Newfunction_call[a].end()), Newfunction_call[a].end());
		}
	}
	function_call = Newfunction_call;
}

// Using the parse data, calculate the support for functions and function pairs,
// and then return the function pairs which we have inferred must always occur together
void analyze()
{
	Pairs = vector<map<int, FunctionPair>>(maxID + 1);
	vector<int> support = vector<int>(maxID, 0);
	int a = 0, b = 0;

	// Calculate support for each function and function pair
	for (map<int, vector<int>>::iterator i = function_call.begin(); i != function_call.end(); ++i)
	{

		vector<int> &v = i->second;
		// Go through all function pairs
		for (int j = 0; j < v.size(); j++)
		{
			a = v[j];
			support[a]++;
			for (int k = 0; k < v.size(); k++)
			{
				b = v[k];
				if (a != b)
				{
					Pairs[a][b].support++;
					Pairs[a][b].a = a;
					Pairs[a][b].b = b;
				} 
			} 
		} 
	} 

	// Calculate confidence for each function pair, and throw out any pairs that don't meet the thresholds
	// Loop through all function pairs
	map<int, FunctionPair>::iterator temp;
	for (int i = 0; i < Pairs.size(); i++)
	{
		for (map<int, FunctionPair>::iterator j = Pairs[i].begin(); j != Pairs[i].end();)
		{
			FunctionPair &p = j->second;
			temp = j;
			++j;
			p.confidence = (float(p.support) * 100.0f) / float(support[p.a]);
			if (p.support < threshhold_support || p.confidence < float(threshhold_confidence))
			{
				// Doesn't meet support or confidence threasholds
				Pairs[i].erase(temp);
			}
		} 
	} 
}

void find_bugs()
{

	// initialize some parameters
	bool found = false;
	int a, b;
	string pairname = "";

	// Look through all top-level functions. 
	// origin_function_call is used because we only want to report each bug once,
	// in the function in which it was originally used.
	for (map<int, vector<int>>::iterator i = origin_function_call.begin(); i != origin_function_call.end(); ++i)
	{
		vector<int> &v = i->second;
		for (int q = 0; q < v.size(); q++)
		{
			a = v[q];
			// Look for all the functions that should be used with any invocation of a
			for (map<int, FunctionPair>::iterator j = Pairs[a].begin(); j != Pairs[a].end(); ++j)
			{
				found = false;
				FunctionPair &p = j->second;
				// See if we find a use of p.b
				for (int k = 0; k < function_call[i->first].size(); k++)
				{
					b = function_call[i->first][k];
					if (p.b == b)
					{
						found = true;
						break;
					}
				}

				// If we don't find a use of p.b, then we have a bug
				if (!found)
				{
					// Admiral Ackbar says: "It's a bug!
					if (id_to_func[p.a] < id_to_func[p.b])
					{
						pairname = demangle(id_to_func[p.a]) + " " + demangle(id_to_func[p.b]);
					}
					else
					{
						pairname = demangle(id_to_func[p.b]) + " " + demangle(id_to_func[p.a]);
					}
					cout << "bug may appear: " << demangle(id_to_func[p.a]) << " in " << demangle(id_to_func[i->first]) << " pair: (" << pairname << ") ";
					cout << "support: " << p.support << " confidence: " << fixed << setprecision(2) << p.confidence << "%" << endl;
				}
			}
		} 
	}
}

void printBitcode(vector<string> &callgraph_tokens)
{
    cout << "original bitcode :" << endl;
    for (int i = 0; i < callgraph_tokens.size(); i++)
    {
        cout << callgraph_tokens[i] << endl;
    }
}

void printFuntionMapping(map<int, string> &id_to_func)
{
    cout << "function map :" << endl;
    for (map<int, string>::iterator it = id_to_func.begin(); it != id_to_func.end(); ++it)
    {
        cout << it->first << " -> " << it->second << " == " << demangle(it->second) << '\n';
    }
}

void printCallFunctions(map<int, vector<int>> &function_call)
{
    cout << endl
         << "call functions:" << endl;
    for (map<int, vector<int>>::iterator it = function_call.begin(); it != function_call.end(); ++it)
    {
        cout << it->first << " calls: ";
        for (int it2 = 0; it2 < it->second.size(); it2++)
        {
            cout << it->second[it2] << " ";
        }
        cout << endl;
    }
	cout << endl;
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
    // Kiểm tra số lượng tham số
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <IPC_LEVELS> <threshhold_support> <threshhold_confidence>" << endl;
        return 1;
    }

    // Gán giá trị từ tham số dòng lệnh
    try
    {
        IPC_LEVELS = stoi(argv[1]);       // Tham số đầu tiên: IPC_LEVELS
        threshhold_support = stoi(argv[2]);       // Tham số thứ hai: threshhold_support
        threshhold_confidence = stoi(argv[3]);    // Tham số thứ ba: threshhold_confidence
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: All arguments must be integers." << endl;
        return 1;
    }
    catch (const out_of_range &e)
    {
        cerr << "Error: Argument value out of range." << endl;
        return 1;
    }

    // In ra các giá trị đã nhận để kiểm tra
    cout << "IPC_LEVELS: " << IPC_LEVELS << endl;
    cout << "threshhold_support: " << threshhold_support << endl;
    cout << "threshhold_confidence: " << threshhold_confidence << endl;

    inputCallgraph(callgraph_tokens); // read the callgraph from standard input
    parser();                         // parse the callgraph

#if DEBUG
    printBitcode(callgraph_tokens); // To see the original Bitcode
    printFuntionMapping(id_to_func);  // To see what we have in those data structure.
    printCallFunctions(function_call);  // To see the call functions with total reduction no edge weight
#endif

    ipc_transform();                 // transform the callgraph for inter-procedural analysis

#if DEBUG
	// To see what we have in those data structure.

	cout << endl
		 << "IPC Call functions :" << endl;
	for (map<int, vector<int>>::iterator it = function_call.begin(); it != function_call.end(); ++it)
	{
		cout << it->first << " calls: ";
		for (int it2 = 0; it2 < it->second.size(); it2++)
		{
			cout << it->second[it2] << " ";
		}
		cout << endl;
	}
#endif

    analyze();                       // analyze the callgraph for function pairs

#if DEBUG
	cout << "Learned Constraints :" << flush << endl;
	// Loop through all function pairs
	for (int i = 0; i < Pairs.size(); i++)
	{
		for (map<int, FunctionPair>::iterator j = Pairs[i].begin(); j != Pairs[i].end(); ++j)
		{
			FunctionPair &p = j->second;
			cout << "pair: (" << demangle(id_to_func[p.a]) << " " << demangle(id_to_func[p.b]) << "), support: "
				 << p.support << ", confidence: " << fixed << setprecision(2) << p.confidence << "%" << endl;
		}
	}
#endif

    find_bugs();                    // find bugs in the callgraph
}