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
  scope5();
  scope6();
  
  return 0;
}

void scope1() {
  A();
  B();
  C();
  D();
}

void scope2() {
  A();
  C();
  D();
}

void scope3() {
  A();
  B();
  scope1();
  scope2();
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
  scope3();
  scope4();
}

void scope6() {
  B();
  D();
  scope3();
}

void A() {
    malloc(0);
  printf("A\n");
    free(0);
}

void B() {
    malloc(0);
    malloc(0);
  printf("B\n");
    free(0);
    free(0);
}

void C() {
  printf("C\n");
  free(0);
  free(0);
}

void D() {
  printf("D\n");
}