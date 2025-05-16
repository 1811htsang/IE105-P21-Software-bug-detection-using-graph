#include <iostream>
using namespace std;

int main() {
    // sample error for compiler to catch and throw
    int a = 5;
    int b = 0;
    int c = a * b; // This will cause a division by zero error
    cout << "Result: " << c << endl; // This line will not be executed due to the error above
    return 0;
}