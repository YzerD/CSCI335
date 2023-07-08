// Yzer De Gula
// main.cc: Tests Min Heap

#include <iostream>
#include "MinHeap.h"


void testMinHeap()
{
    
    MinHeap<int> heap1;
    std::cout << "Empty Heap: " << std::endl;
    heap1.display();


    heap1.insert(5);
    heap1.insert(10);
    heap1.insert(15);


    std::cout << "After Inserting 5, 10, and 15 " << std::endl;
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Heap 1 - Minimum Element: " << heap1.getMin() << std::endl;
    heap1.display();

    std::cout << "After Popping 5 " << std::endl;
    heap1.deleteMin();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Heap 1 - Minimum Element After Deleting: " << heap1.getMin() << std::endl;
    heap1.display();

    std::cout << "After Popping 10 and 15 (Empty Heap)" << std::endl;
    heap1.deleteMin();
    heap1.deleteMin();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Heap 1 - Minimum Element After Deleting: " << heap1.getMin() << std::endl;
    heap1.display();
}

int main()
{
    testMinHeap();
    return 0;
}
