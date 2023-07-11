// Yzer De Gula
// MaxHeap.h Class for a Max Heap that holds Customer Objects

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Customer.h"


// Max Heap Implementation
template <typename Comparable>
class MaxHeap
{
    public:
        // Default Constructor
        MaxHeap() : current_size_(0), array_(MAX_SIZE + 1)
        {} // End Default Constructor


        // Parameterized Constructor (L-Value)
        MaxHeap(const std::vector<Comparable> &elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");
            
            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (L-Value)

        
        // Parameterized Constructor (R-Value)
        MaxHeap(std::vector<Comparable> &&elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (R-Value)


        // Copy Constructor 
        MaxHeap(const MaxHeap &rhs) : current_size_(rhs.current_size_), array_(rhs.array_)
        {} // End Copy Constructor


        // Copy Assignment
        MaxHeap& operator=(const MaxHeap &rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            heapify();

            return *this;
        } // End Copy Assignment


        // Move Constructor
        MaxHeap(MaxHeap &&rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            rhs.current_size_ = 0;
        } // End Move Constructor


        // Move Assignment
        MaxHeap& operator=(MaxHeap &&rhs)
        {
            std::swap(current_size_, rhs.current_size_);
            std::swap(array_, rhs.array_);

            rhs.current_size_ = 0;

            return *this;
        } // End Move Assignment


        // Destructor
        ~MaxHeap()
        {
            current_size_ = 0;
        } // End Destructor

        
        // Assignment Overload
        MaxHeap& operator=(const std::vector<Comparable> &elements)
        {
            current_size_ = elements.size();
            array_.resize(MAX_SIZE + 1);

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            heapify();

            return *this;
        } // End Assignment Overload


        // insert
        void insert(const Comparable &new_item)
        {
            if (isFull())
                throw std::out_of_range("Heap if full, Unable to insert element.\n");
            
            int hole = ++current_size_;
            while (hole > 1 && new_item > array_[hole/2])
            {
                array_[hole] = array_[hole/2];
                hole = hole/2;
            }
            array_[hole] = new_item;
        } // End insert


        // deleteMax
        void deleteMax()
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty. No maximum element present.\n");

            array_[1] = array_[current_size_];
            current_size_--;
            percolateDown(1);
        } // End deleteMax


        // heapify
        void heapify()
        {
            for (int i = current_size_ / 2; i > 0; i--)
                percolateDown(i);
        } // End heapify


        // getMax
        int getMax() const
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty, No maximum element present.\n");
            
            return array_[1];
        } // End getMax

        
        // getCurrentSize
        int getCurrentSize() const
        {
            return current_size_;
        } // End getCurrentSize


        // display
        void display() const
        {
            if (isEmpty())
                std::cout << "  Heap is Empty." << std::endl;

            for (size_t i = 1; i <= current_size_; i++)
            {
                std::cout << "  Index[" << i << "]: " << array_[i];

                size_t left_child_index = 2 * i;
                size_t right_child_index = 2 * i + 1;

                if (left_child_index <= current_size_)
                    std::cout << ", Left Child[" << left_child_index << "]: " << array_[left_child_index];

                if (right_child_index <= current_size_)
                    std::cout << ", Right Child[" << right_child_index << "]: " << array_[right_child_index];

                std::cout << std::endl;
            }
            std::cout << std::endl;
        } // End display

    private:
        static const int MAX_SIZE = 100;
        std::vector<Comparable> array_;
        size_t current_size_;

        void percolateDown( int hole )
        {
            int child;
            Comparable temp = array_[hole];

            while (2 * hole <= current_size_)
            {
                child = hole * 2;
                if (child != current_size_ && array_[child + 1] > array_[child])
                    child++;
                
                if (array_[child] > temp)
                    array_[hole] = array_[child];
                else
                    break;
                
                hole = child;
            }
            array_[hole] = temp;
        } 

        bool isEmpty() const
        {
            return current_size_ == 0;
        }

        bool isFull() const
        {
            return current_size_ == MAX_SIZE;
        }

};



// serviceTimeComparison
bool serviceTimeComparison(const Customer &customer1, const Customer &customer2)
{
    return customer1.getServiceTime() < customer2.getServiceTime();
} // End serviceTimeComparison


// Max Heap Implementation to Store Customer
template<>
class MaxHeap<Customer>
{
    public:
        // Default Constructor
        MaxHeap() : current_size_(0), array_(MAX_SIZE + 1)
        {} // End Default Constructor


        // Parameterized Constructor (L-Value)
        MaxHeap(const std::vector<Customer> &elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");
            
            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (L-Value)

        
        // Parameterized Constructor (R-Value)
        MaxHeap(std::vector<Customer> &&elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (R-Value)


        // Copy Constructor 
        MaxHeap(const MaxHeap &rhs) : current_size_(rhs.current_size_), array_(rhs.array_)
        {} // End Copy Constructor


        // Copy Assignment
        MaxHeap& operator=(const MaxHeap &rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            heapify();

            return *this;
        } // End Copy Assignment


        // Move Constructor
        MaxHeap(MaxHeap &&rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            rhs.current_size_ = 0;
        } // End Move Constructor


        // Move Assignment
        MaxHeap& operator=(MaxHeap &&rhs)
        {
            std::swap(current_size_, rhs.current_size_);
            std::swap(array_, rhs.array_);

            rhs.current_size_ = 0;

            return *this;
        } // End Move Assignment


        // Destructor
        ~MaxHeap()
        {
            current_size_ = 0;
        } // End Destructor

        
        // Assignment Overload
        MaxHeap& operator=(const std::vector<Customer> &elements)
        {
            current_size_ = elements.size();
            array_.resize(MAX_SIZE + 1);

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            heapify();

            return *this;
        } // End Assignment Overload


        // insert
        void insert(const Customer &new_item)
        {
            if (isFull())
                throw std::out_of_range("Heap if full, Unable to insert element.\n");
            
            int hole = ++current_size_;
            while (hole > 1 && new_item.getPriorityLevel() > array_[hole/2].getPriorityLevel())
            {
                array_[hole] = array_[hole/2];
                hole = hole/2;
            }
            array_[hole] = new_item;
        } // End insert


        // deleteMax
        Customer deleteMax()
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty. No maximum element present.\n");

            Customer maxCustomer = array_[1];
            array_[1] = array_[current_size_];
            current_size_--;
            percolateDown(1);

            maxCustomer.setServiceTime();

            history_.push_back(maxCustomer);
            std::sort(history_.begin(), history_.end(), serviceTimeComparison);
            
            return maxCustomer;
        } // End deleteMax


        // heapify
        void heapify()
        {
            for (int i = current_size_ / 2; i > 0; i--)
                percolateDown(i);
        } // End heapify


        // getMax
        Customer getMax() const
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty, No maximum element present.\n");
            
            return array_[1];
        } // End getMax

        
        // getCurrentSize
        int getCurrentSize() const
        {
            return current_size_;
        } // End getCurrentSize


        // display
        void display() const
        {
            std::cout << "Heap: " << std::endl;

            if (isEmpty())
                std::cout << "  Heap is Empty." << std::endl << std::endl;

            for (size_t i = 1; i <= current_size_; i++)
            {
                std::cout << "  Index[" << i << "]: " << array_[i];

                size_t left_child_index = 2 * i;
                size_t right_child_index = 2 * i + 1;

                if (left_child_index <= current_size_)
                {
                    std::cout << "  Left Child[" << left_child_index << "]: " << array_[left_child_index];
                    if (right_child_index <= current_size_)
                        std::cout << "  Right Child[" << right_child_index << "]: " << array_[right_child_index];
                }

                std::cout << std::endl;
            }
        } // End display

    
        // displayHistory
        void displayHistory() const
        {
            std::cout << "History: ";
            if (history_.size() == 0)
                std::cout << "  History is Empty." << std::endl;

            for (auto x : history_)
                std::cout << x;
            
            std::cout << std::endl;
        } // End displayHistory

    private:
        static const int MAX_SIZE = 100;
        std::vector<Customer> array_;
        std::vector<Customer> history_;
        size_t current_size_;

        // percolateDown
        void percolateDown( int hole )
        {
            int child;
            Customer temp = array_[hole];

            while (2 * hole <= current_size_)
            {
                child = hole * 2;
                if (child != current_size_ && array_[child + 1].getPriorityLevel() > array_[child].getPriorityLevel())
                    child++;
                
                if (array_[child].getPriorityLevel() > temp.getPriorityLevel())
                    array_[hole] = array_[child];
                else
                    break;
                
                hole = child;
            }
            array_[hole] = temp;
        } // End percolateDown


        // isEmpty
        bool isEmpty() const
        {
            return current_size_ == 0;
        } // End isEmpty


        // isFull
        bool isFull() const
        {
            return current_size_ == MAX_SIZE;
        } // End isEmpty

};

#endif // MAXHEAP_H