#include "stdio.h"

/*
The types of situations the inter-procedural analysis can help with are:
Pairs of function calls which are usually used together, but used indirectly through intermediate functions. With IPC, we can have higher support and confidence for these pairs than we would have had otherwise.
Potential bugs (A called without B) where the function B is called, but through a helper function. With IPC, we can avoid reporting these as potential bugs, because the situation is under control.
Note that IPC only helps up to the specified depth, structure beyond that depth is lost.

For this example program, no bugs are found with IPC_LEVELS set to 1. The structure in this program is deeper than 1 level, as most of the time at least some of the A, B, C, and D function calls are hidden inside helper functions. In fact, looking at intermediate output, we cannot even learn any constraints on which functions should be used together.

When run with IPC_LEVELS set to 2, we find 5 bugs. In this case, the bugs in help1 and help2 are spurious: these helper functions are always called with the correct context (but this fact is too complicated for our program to understand). The lack of bugs in scope1 and scope4 


bug: B in help1 pair: (A B) support: 4 confidence: 66.67%
bug: B in scope2 pair: (B D) support: 5 confidence: 83.33%
bug: A in scope3 pair: (A B) support: 4 confidence: 66.67%
bug: A in help2 pair: (A B) support: 4 confidence: 66.67%
bug: A in help2 pair: (A D) support: 4 confidence: 66.67%
bug: D in help3 pair: (B D) support: 5 confidence: 71.43%


*/

void scope1();
void scope2();
void scope3();
void scope4();
void scope5();

void help1();
void help2();
void help3();

void A();
void B();
void C();
void D();



int main() {
  scope1();
  scope2();
  scope3();
  scope4();
  scope5();
  return 0;
}

void help1() {
  B();
  D();
}

void help2() {
  A();
}

void help3() {
  D();
}

void scope1() {
  A();
  B();
  C();
  D();
}

void scope2() {
  B();
  help2();
}

void scope3() {
  A();
  help3();
}

void scope4() {
  help1();
  help2();
}

void scope5() {
  help1();
  help3();
}

void A() {
  printf("A\n");
}

void B() {
  printf("B\n");
}

void C() {
  printf("C\n");
}

void D() {
  printf("D\n");
}

