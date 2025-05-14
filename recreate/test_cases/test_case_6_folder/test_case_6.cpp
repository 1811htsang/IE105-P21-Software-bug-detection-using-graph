#include "stdio.h"
#include <stdlib.h>

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
  
  return 0;
}

void scope1() {
  A();
}

void scope2() {
  A();
  C();
  D();
}

void scope3() {
  A();
  scope2();
}

void scope4() {
  B();
  C();
  D();
  scope1();
  scope2();
  scope3();
}

void scope5() {
  B();
  C();
  A();
  scope1();
  scope3();
}

void scope6() {
  B();
  D();
  scope3();
}

void A() {
  int *p = new int[10];
  int q = 0;
  for (int i = 0; i < 10; i++) {
    p[i] = i;
  }
  printf("A\n");
  delete[] p;
  p = nullptr;
}

void B() {
  int *q = new int[10];
  printf("B\n");
  A();
}

void C() {
  printf("C\n");
  int *p = new int;
  *p = 0;
  delete p;
  A();
}

void D() {
  A();
  B();
  printf("D\n");
}