#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n)
{
    if (n <= 0) return false;
    if (n > 1 && n <= 3) return true;
    for (int i = 2; i <= n - 1; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}
int main() {
    cout << boolalpha;
    int n; cin >> n;
    cout << isPrime(n);
    return 0;
}