#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    // OK
    int * p = new int;
    delete p; 

    // Memory leak
    int * q = new int;
    // no delete
}