#include <iostream>
using namespace std;

int main() {
  bool x[4][13];

  for (i = 1; i <= 13; i++) {
    if (x[0][i] == 0) {
      cout << "S " << i << endl;
    } else {
      cout << "n";
    }
  }
}