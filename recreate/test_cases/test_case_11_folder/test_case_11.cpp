#include "stdio.h"

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

  int a[5] = {1, 2, 3, 4, 5};
  printf("%d\n", a[3]);
}

void B() {
  printf("B\n");
}

void C() {
  printf("C\n");
  int i = 10;
  while (i > 0) {
    printf("%d\n", i);
    i++;
    if (i > 10) {
      break;
    }
  }
}

void D() {
  printf("D\n");
}