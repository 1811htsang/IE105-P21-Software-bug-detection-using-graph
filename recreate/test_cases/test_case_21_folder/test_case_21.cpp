#include<iostream>
using namespace std;
int main ()
{
    int num, temp, rem, sum = 0;
    cout << "Enter number to be checked : ";
    num = 153; //cin >> num;
    temp = num;
    while (temp != 0)
    {
        rem = temp % 10;
        sum = sum + rem*rem*rem;
        temp = temp / 10;
    }
    if (sum == num)
        cout << "\n" << num << " is an Armstrong number.";
    else
        cout << "\n" << num << " is not an Armstrong number.";
    return 0;
}