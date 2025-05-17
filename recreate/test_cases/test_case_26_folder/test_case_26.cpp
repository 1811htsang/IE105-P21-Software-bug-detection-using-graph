#include <iostream>
// include random header for random number generation
#include <cstdlib>
#include <ctime>

 

int main()

{

    int size = 5;

    int sizex, sizey;

    


    // One-dimensional array

    int *arr = new int[size];

    for (int i = 0; i < size; i++)

        arr[i] = rand() % 100; // fill with random numbers

    delete[] arr;

    // Two-dimensional array

    std::cout << "Enter the size of two-dimensional array ";

    sizex = 3;
    sizey = 4;

    int ** arr_2d = new int*[sizex];

    for(int i = 0; i < sizex; i++)

        arr_2d[i] = new int[sizey];

    for (int i = 0; i < sizex; i++)

    {

        for(int j = 0; j < sizey; j++)

            arr_2d[i][j] = rand() % 100; // fill with random numbers

    }

    // Deleting array completely

    for(int i = 0;i < sizex; i++)    

        delete[] arr_2d[i];

}