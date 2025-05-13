#include <bits/stdc++.h>
using namespace std;
#define optimize()                                                             \\
  ios_base::sync_with_stdio(0);                                                \\
  cin.tie(0);                                                                  \\
  cout.tie(0);
#define endl '\\n'
int main() {
  optimize();
  int i, j, k, n;
  cin >> n;
  long long sum = 0;
  for (i = 1; i < n; i++) {
    for (j = 1; j < n; j++) {
      for (k = 1; k < n; k++) {
        if (i * j + k == n)
          sum++;
      }
    }
  }
  cout << sum << endl;
  return 0;
}
