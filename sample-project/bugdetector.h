#ifndef _PIPAIR_
#define _PIPAIR_

#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

enum {
  PIPE_READ = 0,
  PIPE_WRITE,
};

class FunctionPair{
  public:
    int a;
    int b;
    int support;
    float confidence;
    
    FunctionPair(): a(0), b(0), support(0), confidence(-1) {}
};

// FUNCTION PROTOTYPES ====================================

string getFuncfromToken(const string &token);

 // Parses the call graph
void parser( );

// Using the parse data, calculate the support for functions and function pairs, and then return the function pairs which we have inferred must always occur together
void analyze( vector<map<int,FunctionPair> > &Pairs );

void find_bugs();

#endif //_PIPAIR_


