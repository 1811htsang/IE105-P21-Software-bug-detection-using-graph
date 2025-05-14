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
  printf("Function B\n");
  A();
  A();
  A();
  printf("Function B\n");
}

void C() {
  printf("Function C\n");
  A();
  B();
  A();
  B();
  printf("Function C\n");
}

void scope1() {
  A();
  B();
  C();
  printf("Function scope1\n");
}

void scope2() {
  C();
  B();

}

void scope3() {
  A();
  B();
  printf("Function scope3\n");
}

void scope4() {
  B();
  C();
  scope1();
}

int main() {
  // printf("hello world\n");
  C();
  B();
  return 0;
}

//  

