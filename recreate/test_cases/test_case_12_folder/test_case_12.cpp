#include "stdio.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void scope1();
void scope2();
void scope3();
void scope4();
void scope5();
void scope6();

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
  scope6();
  
  return 0;
}

void scope1() {
  A();
  B();
  C();
  malloc(0);
  D();
  A();
  free(0);
}

void scope2() {
    free(0);
  A();
  C();
  D();
}

void scope3() {
    malloc(0);
    malloc(0);
  A();
  B();
}

void scope4() {
  B();
  D();
  scope1();
}

void scope5() {
  B();
  D();
  A();
}

void scope6() {
  B();
  D();
}

void A() {
  printf("A\n");
  int i;
  cout << (i++) * (++i) - (i--);
}

void B() {
  printf("B\n");
}

void C() {
  printf("C\n");
  int i;
  while (i > 0) {
    printf("%d\n", i);
    i--;
  }
}

void D() {
  printf("D\n");
}