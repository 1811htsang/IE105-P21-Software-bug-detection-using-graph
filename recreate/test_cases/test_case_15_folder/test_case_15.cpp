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
    int x = rand() % 10; // Sinh số ngẫu nhiên từ 0 đến 9
    return x + 1;
}

int B() {
    int x = rand() % 10;
    return x - 1;
}

int C() {
    int x = rand() % 10;
    return x * 2;
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
    cout << "Scope 2: " << C() << ", " << D() << endl;
}

void scope3() {
    cout << "Scope 3: " << A() * B() << ", " << C() * D() << endl;
}

void scope4() {
    vector<int> results = {A(), B(), C(), D()};
    cout << "Scope 4: ";
    for (int r : results) {
        cout << r << " ";
    }
    cout << endl;
}