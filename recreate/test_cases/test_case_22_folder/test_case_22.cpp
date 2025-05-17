#include <cstring>

#include <iostream>

#include <cstdlib>

#define ll long long

using namespace std;

 

/* 

 * Recursive function to find Fibonnaci Numbers

 */

ll fibo_recur(int n)

{

    if (n == 1 || n == 2)

        return 1;

    else

        return fibo_recur(n - 1) + fibo_recur(n - 2);;

}

/* 

 * Main

 */

int main()

{

    int n;

        cout<<"Enter the integer n to find nth fibonnaci no.(0 to exit): ";

        n = 15;

        cout<<fibo_recur(n)<<endl;

    return 0;

}