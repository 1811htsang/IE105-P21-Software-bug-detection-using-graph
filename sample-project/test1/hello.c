#include <stdio.h>
#include <stdlib.h>

void A() {
  printf("Function A\n");
  system("echo \"function A calling\"");
  for (int i = 0; i < 3; i++) {
    printf("Function A loop %d\n", i);
  }
  printf("Function A end\n");
}

void B() {
  A();
  A();
  A();
  printf("Function B\n");
}

void C() {
  A();
  B();
  A();
  B();
  printf("Function C\n");
}

int main() {
  printf("hello world\n");
  C();
  B();
  return 0;
}

