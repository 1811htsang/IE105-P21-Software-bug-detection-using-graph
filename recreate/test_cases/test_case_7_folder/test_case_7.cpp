#include <iostream>
using namespace std;

int main() {
  bool x[4][13];
  int number, n, i;
  char mark;

  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> mark >> number;
    if (mark == 'S') {
      x[0][number] = 1;
    } else if (mark == 'H') {
      x[1][number] = 1;
    } else if (mark == 'C') {
      x[2][number] = 1;
    } else if (mark == 'D') {
      x[3][number] = 1;
    }
  }

  for (i = 1; i <= 13; i++) {
    if (x[0][i] == 0) {
      cout << "S " << i << endl;
    }
  }
  for (i = 1; i <= 13; i++) {
    if (x[1][i] == 0) {
      cout << "H " << i << endl;
    }
  }
  for (i = 1; i <= 13; i++) {
    if (x[2][i] == 0) {
      cout << "C " << i << endl;
    }
  }
  for (i = 1; i <= 13; i++) {
    if (x[3][i] == 0) {
      cout << "D " << i << endl;
    }
  }
}