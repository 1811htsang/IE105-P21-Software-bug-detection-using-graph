#include <bits/stdc++.h>
using namespace std;
bool isprime(int p) {
  int i = 2;
  while (i <= sqrt(p)) {
    if (p % i == 0) {
      return false;
    }
    i++;
  }
  return true;
}
int main() {
  int number = 123;
  cout << "The number is: " << number << endl;
  cout << isprime(number) << endl;
}
