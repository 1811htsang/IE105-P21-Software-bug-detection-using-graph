#include <iostream>
using namespace std;

void scope1() {
  int i = 10;
  while (i > 0) {
    cout << i << endl;
    i--;
  }
  cout << "Scope 1" << endl;
}

void scope2() {
  cout << "Scope 2" << endl;
}

void recursion(int n, int m) {
  if (n == 0) {
    cout << m << endl;
    scope1();
    return;
  }
  recursion(n - 1, m + 1);
}

int main() {
  int n;
  int m;
  m = 10;
  n = 5;
  recursion(n, m);
}