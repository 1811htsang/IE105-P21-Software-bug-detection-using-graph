#include "stdio.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int A() {
    int x = 0;
    return (x - 2);
}

int B() {
    int x = 0;
    return (x - 1);
}

int C() {
    int x = 0;
    return (x + 1);
}

int D() {
    int x = 0;
    return (x + 2);
}

void scope1() {
    cout << A() << B() << endl;
    cout << C() << D() << endl;
}

void scope2() {
    cout << A() * B() << endl;
    cout << C() * D() << endl;
}

void scope3() {
    scope1();
    int a = A();
}

void scope4() {
    scope2();
    int b = B();
}

int main() {
  scope1();
  scope2();
  scope3();
  scope4();
  return 0;
}

