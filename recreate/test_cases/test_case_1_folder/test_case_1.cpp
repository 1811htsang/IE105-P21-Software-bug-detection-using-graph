#include <iostream>
using namespace std;

int main() {
  

  int value[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = sizeof(value) / sizeof(value[0]);

  int max;
  max = value[1] - value[0];

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (max < value[j] - value[i]) {
        max = value[j] - value[i];
      }
    }
  }

  cout << max << endl;

  return 0;
}