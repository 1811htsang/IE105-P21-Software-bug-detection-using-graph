#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<int> vec(10);
  for (int i = 0; i < 10; i++) {
    cin >> vec[i];
  }
  while (1) {
    int a, b = 0;
    for (int j = 0; j < 10; j++) {
      if (vec[j] > vec[j + 1] && j + 1 < 10) {
        a = 0;
        a = vec[j];
        vec[j] = vec[j + 1];
        vec[j + 1] = a;
        b++;
      }
    }
    if (b == 0)
      break;
  }
  for (int i = 9; i >= 7; i++) {
    cout << vec[i] << endl;
  }
  return 0;
}