#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, ans = 0;
  cin >> N;

  int A = 1, B = 1, C = 1;

  int sum = 0;
  // Aの操作
  while (sum <= N / 2) {
    if (A * B > N) {
      break;
    }
    // Bの操作
    while (sum <= N / 2) {
      if (A * B > N) {
        break;
      }
      // Cの操作
      while (sum <= N) {
        // 計算
        sum = A * B + C;
        // Nと一致したら
        if (sum == N) {
          ans++;
        }
        sum = 0;
        C++;
      }
      C = 1;
      B++;
    }
    B = 1;
    C = 1;
    A++;
  }

  cout << ans << endl;
}