#include <bits/stdc++.h>
#define MAX 300
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n = 7;
    if (n < 3 || n > 10){
        cout << "Khong thoa dieu kien nhap.";
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i; j++) {
                cout << " " << " ";
            }
            for (int k = 1; k <= i; k++) {
                cout << "*" << " ";
            }
            cout << endl;
        }
    }
    
    return 0;
}