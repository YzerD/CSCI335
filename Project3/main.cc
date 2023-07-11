// Yzer De Gula
// main.cc: Tests Max Heap and Customer

#include <iostream>
#include "MaxHeap.h"
#include "Customer.h"


void testMaxHeap()
{
    
    MaxHeap<int> heap1;
    std::cout << "Empty Heap: " << std::endl;
    heap1.display();


    heap1.insert(5);
    heap1.display();
    heap1.insert(10);
    heap1.insert(15);


    std::cout << "After Inserting 5, 10, and 15: " << std::endl;
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Maximum Element: " << heap1.getMax() << std::endl;
    heap1.display();

    std::cout << "After Popping 5: " << std::endl;
    heap1.deleteMax();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Maximum Element After Deleting: " << heap1.getMax() << std::endl;
    heap1.display();

    std::cout << "After Popping 10 and 15 (Empty Heap):" << std::endl;
    heap1.deleteMax();
    heap1.deleteMax();
    std::cout << "Current Size: " << heap1.getCurrentSize() << std::endl;
    std::cout << "Maximum Element After Deleting All Elements: " << heap1.getMax() << std::endl;
    heap1.display();

}


void testMaxHeap2()
{
    // TESTS PARAMETERIZED CONSTRUCTOR (L-VALUE)
    std::vector<int> elements = {9,5,2,7,1,8};
    MaxHeap<int> heap2(elements);
    std::cout << "Heap 2: " << std::endl; heap2.display();

    // TESTS COPY CONSTRUCTOR
    std::cout << "After Copy Constructor heap3{heap2}: " << std::endl;
    MaxHeap<int> heap3(heap2);
    std::cout << "Heap 3: " << std::endl; heap3.display();

    // TESTS PARAMETERIZED CONSTRUCTOR (R-VALUE) & COPY ASSIGNMENT
    MaxHeap<int> heap4(std::vector<int>{50,60,70,75,100});
    std::cout << "Heap 4 Before Copy Assignment: " << std::endl;
    std::cout << "Heap 4: " << std::endl; heap4.display();
    std::cout << "After heap4 = heap2 " << std::endl;
    heap4 = heap2;
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE CONSTRUCTOR
    MaxHeap<int> heap5 = std::move(heap4);
    std::cout << "After heap 5= std::move(heap4) " << std::endl; 
    std::cout << "Heap 5: " << std::endl; heap5.display();
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE ASSIGNMENT
    MaxHeap<int> heap6(std::vector<int>{17,21,16,76});
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


void testCustomer()
{
    // TEST DEFAULT CONSTRUCTOR 
    Customer cusomter1;
    std::cout << "Default Constructor: " << std::endl;
    std::cout << "Customer 1: " << std::endl; cusomter1.display();

    // TEST MUTATORS
    std::cout << "After Mutators: " << std::endl;
    cusomter1.setName("Joe Mama");
    cusomter1.setServiceTime(60);
    cusomter1.setPriorityLevel(29);
    std::cout << "Customer 1: " << std::endl; cusomter1.display();

    // TEST OVERLOADED MUTATORS
    cusomter1.setServiceTime();
    cusomter1.setPriorityLevel();
    std::cout << "After Overloaded Mutators: " << std::endl;
    std::cout << "Customer 1: " << std::endl; cusomter1.display();

    // TEST PARAMETERIZED & COPY CONSTRUCTOR
    std::cout << "1 Parameter Constructor: " << std::endl;
    Customer customer2("Uno");
    std::cout << "Customer 2: " << std::endl; customer2.display();

    std::cout << "2 Parameter Constructor: " << std::endl;
    Customer customer3("Ryan", 60);
    std::cout << "Customer 3: " << std::endl; customer3.display();

    std::cout << "Copy Constructor customer4(customer1): " << std::endl;
    Customer customer4(cusomter1);
    std::cout << "Customer 4: " << std::endl; customer4.display();

    // TEST COPY ASSIGNMENT
    customer4 = customer3;
    std::cout << "Copy Assignment customer4 = customer3: " << std::endl;
    std::cout << "Customer 4: " << std::endl; customer4.display();

    // TEST MOVE CONSTRUCTOR
    Customer customer5 = std::move(customer2);
    std::cout << "Move Constructor customer5 = move(customer2): " << std::endl;
    std::cout << "Customer 5: " << std::endl; customer5.display();
    std::cout << "Customer 2: " << std::endl; customer2.display();

    // TEST MOVE ASSIGNMENT
    customer2 = std::move(customer4);
    std::cout << "Move Assignment customer2 = move(customer4): " << std::endl;
    std::cout << "Customer 2: " << std::endl; customer2.display();
    std::cout << "Customer 4: " << std::endl; customer4.display();
}


void testCustomer2()
{
    MaxHeap<Customer> heap1;
    std::cout << "Empty Heap: " << std::endl;
    heap1.display();

    Customer customer1("Joe Mama");
    // customer1.display();
    heap1.insert(customer1);
    std::cout << "After Inserting 1 Customer: " << std::endl;
    heap1.display();

    Customer customer2("Jeff");
    Customer customer3("Jeremy");
    heap1.insert(customer2);
    heap1.insert(customer3);
    std::cout << "After Inserting 2 More Customers: " << std::endl;
    heap1.display();

    heap1.displayHistory();
    heap1.deleteMax();
    std::cout << "Heap After Deleting 1: " << std::endl;
    heap1.display();
    heap1.displayHistory();
    heap1.deleteMax();
    heap1.deleteMax();

    std::cout << "Heap After Deleting All: " << std::endl;
    heap1.display();
    heap1.displayHistory();

}


void testMaxHeapCustomer()
{
    // TESTS PARAMETERIZED CONSTRUCTOR (L-VALUE)
    Customer customer1("Joe");
    Customer customer2("Trump");
    Customer customer3("Obama");
    std::vector<Customer> elements = {customer1, customer2, customer3};
    MaxHeap<Customer> heap2(elements);
    std::cout << "Heap 2: " << std::endl; heap2.display();

    // TESTS COPY CONSTRUCTOR
    std::cout << "After Copy Constructor heap3{heap2}: " << std::endl;
    MaxHeap<Customer> heap3(heap2);
    std::cout << "Heap 3: " << std::endl; heap3.display();

    // TESTS PARAMETERIZED CONSTRUCTOR (R-VALUE) & COPY ASSIGNMENT
    Customer customer4("George");
    Customer customer5("Bill");
    MaxHeap<Customer> heap4(std::vector<Customer>{customer4, customer5});
    std::cout << "Heap 4 Before Copy Assignment: " << std::endl;
    std::cout << "Heap 4: " << std::endl; heap4.display();
    std::cout << "After heap4 = heap2 " << std::endl;
    heap4 = heap2;
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE CONSTRUCTOR
    MaxHeap<Customer> heap5 = std::move(heap4);
    std::cout << "After heap 5= std::move(heap4) " << std::endl; 
    std::cout << "Heap 5: " << std::endl; heap5.display();
    std::cout << "Heap 4: " << std::endl; heap4.display();

    // TESTS MOVE ASSIGNMENT
    Customer customer6("Wilson");
    Customer customer7("Madison");
    Customer customer8("Adams");
    MaxHeap<Customer> heap6(std::vector<Customer>{customer6, customer7, customer8});
    std::cout << "Heap 6: " << std::endl; heap6.display();
    std::cout << "Heap 5: " << std::endl; heap5.display();
    std::cout << "After heap5 = std::move(heap6): " << std::endl;
    heap5 = std::move(heap6);
    std::cout << "Heap 6: " << std::endl; heap6.display();
    std::cout << "Heap 5: " << std::endl; heap5.display();

    // TESTS OVERLOADED ASSIGNMENT
    Customer customer9("Lincoln");
    Customer customer10("Taft");
    heap5 = std::vector<Customer>{customer9, customer10};
    std::cout << "Testing heap5 = std::vector<int>{customer9, customer10}" << std::endl;
    std::cout << "Heap 5: " << std::endl; heap5.display();
}

int main()
{
    //testMaxHeap();
    testMaxHeap2();
    testCustomer();
    testCustomer2();
    testMaxHeapCustomer();
    return 0;
}