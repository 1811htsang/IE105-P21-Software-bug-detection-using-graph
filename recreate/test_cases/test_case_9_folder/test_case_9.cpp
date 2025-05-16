#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char *argv[]) {
  int n, x, count = 0;
  n = 2;

  for (int i = 0; i < n; i++) {
    x = 300;

    if (!(x % 2)) {
      bool flag = true;
      for (int j = 3; i < sqrt(x); j += 2) {
        if (!(x % j)) {
          flag = false;
          break;
        }
      }
      if (flag)
        count++;
    }
  }

  cout << count << endl;
}