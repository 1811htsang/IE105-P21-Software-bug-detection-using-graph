#include <iostream>
#include <vector>
#include <cstdlib>

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
    return -1;
}

int B() {
    return 0;
}

int D() {
    int x = rand() % 10;
    return x / 2;
}

// Định nghĩa các phạm vi
void scope1() {
    cout << "Scope 1: " << A() << ", " << B() << endl;
}

void scope2() {
    scope1();
    cout << "Scope 2: " << C() << ", " << D() << endl;
}

void scope3() {
    cout << "Scope 3: " << A() * B() << ", " << C() * D() << endl;
}

void scope4() {
    scope1();
    scope2();
    cout << endl;
}