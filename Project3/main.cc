// Yzer De Gula
// main.cc: Tests Max Heap and Customer

#include <iostream>
#include "MaxHeap.h"
//#include "Customer.h"

void testMaxHeap()
{
    MaxHeap<int> heap1;


    const auto& arr_1 = heap1.getArray();
    int size_1 = heap1.getCurrentSize();

    for (int i = 0; i <= size_1; i++)
    {
        std::cout << "Array[" << i << "]: " << arr_1[i] << std::endl;
    }
    std::cout << "Current Size: " << size_1 << std::endl;

    std::cout << "Heap 1 - Maximum Element: " << heap1.getMax() << std::endl;
}

int main()
{
    testMaxHeap();
    return 0;
}

/*
    Make Constructors, Destructor, and solve Private Var situation, Max Heap with the arrays with the + 1 or the vector
*/