#include <stdio.h>

void A() {
  printf("Function A\n");
}

void B() {
  A();
  B();
  printf("Function B\n");
}

void C() {
  A();
  C();
  printf("Function C\n");
}

int main() {
  printf("hello world\n");
  C();
  B();
  return 0;
}

