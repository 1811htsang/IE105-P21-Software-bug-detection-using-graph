#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

// Khai báo các hàm
int A();
int B();
int C();
int D();

void scope1();
void scope2();
void scope3();
void scope4();

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
    // Gọi các phạm vi thử nghiệm
    scope1();
    scope2();
    scope3();
    scope4();
    return 0;
}

// Định nghĩa các hàm
int A() {
    return 2 + 2;
}

int C() {
    int x = 0;
    cout << isprime(x) << endl; // In ra kết quả kiểm tra số nguyên tố
    return x;
}

int D() {
    return 1;
}

// Định nghĩa các phạm vi
void scope1() {
    cout << "Scope 1: ";
}

void scope2() {
    cout << "Scope 2: " << C() << ", " << D() << endl;
    cout << "Scope 2: " << B() << endl;
    scope1();
}

void scope3() {
    cout << "Scope 3: " << B() << endl;
    cout << "Scope 3: " << B() << ", " << C() * D() << endl;
    scope1();
    scope2();
}

void scope4() {
    cout << "Scope 4: " << A() << ", " << B() << endl;
    cout << "Scope 4: " << A() * B() << ", " << C() * D() << endl;
    scope1();
    scope2();
    scope3();
}