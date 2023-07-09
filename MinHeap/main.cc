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


    std::cout << "After Inserting 5, 10, and 15: " << std::endl;
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Minimum Element: " << heap1.getMin() << std::endl;
    heap1.display();

    std::cout << "After Popping 5: " << std::endl;
    heap1.deleteMin();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Minimum Element After Deleting: " << heap1.getMin() << std::endl;
    heap1.display();

    std::cout << "After Popping 10 and 15 (Empty Heap):" << std::endl;
    heap1.deleteMin();
    heap1.deleteMin();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Minimum Element After Deleting All Elements: " << heap1.getMin() << std::endl;
    heap1.display();

}

void testMinHeap2()
{
    // TESTS PARAMETERIZED CONSTRUCTOR (L-VALUE)
    std::vector<int> elements = {9,5,2,7,1,8};
    MinHeap<int> heap2(elements);
    std::cout << "Heap 2: " << std::endl; heap2.display();

    // TESTS COPY CONSTRUCTOR
    std::cout << "After Copy Constructor heap3{heap2}: " << std::endl;
    MinHeap<int> heap3(heap2);
    std::cout << "Heap 3: " << std::endl; heap3.display();

    // TESTS PARAMETERIZED CONSTRUCTOR (R-VALUE) & COPY ASSIGNMENT
    MinHeap<int> heap4(std::vector<int>{50,60,70,75,100});
    std::cout << "Heap 4 Before Copy Assignment: " << std::endl;
    std::cout << "Heap 4: " << std::endl; heap4.display();
    std::cout << "After heap4 = heap2 " << std::endl;
    heap4 = heap2;
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE CONSTRUCTOR
    MinHeap<int> heap5 = std::move(heap4);
    std::cout << "After heap 5= std::move(heap4) " << std::endl; 
    std::cout << "Heap 5: " << std::endl; heap5.display();
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE ASSIGNMENT
    MinHeap<int> heap6(std::vector<int>{17,21,16,76});
    std::cout << "Heap 6: " << std::endl; heap6.display();
    std::cout << "Heap 5: " << std::endl; heap5.display();
    std::cout << "After heap5 = std::move(heap6): " << std::endl;
    heap5 = std::move(heap6);
    std::cout << "Heap 6: " << std::endl; heap6.display();
    std::cout << "Heap 5: " << std::endl; heap5.display();

    // TESTS OVERLOADED ASSIGNMENT
    heap5 = std::vector<int>{69,420};
    std::cout << "Testing heap5 = std::vector<int>{69,420}" << std::endl;
    std::cout << "Heap 5: " << std::endl; heap5.display();

}

int main()
{
    testMinHeap();
    //testMinHeap2();
    return 0;
}
