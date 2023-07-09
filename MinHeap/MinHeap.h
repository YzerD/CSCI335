// Yzer De Gula
// MinHeap.h Template Class for a Min Heap

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
#include <iostream>



// Min Heap Implementation
template <typename Comparable>
class MinHeap
{
    public:
        // Default Constructor
        MinHeap() : current_size_(0), array_(MAX_SIZE + 1)
        {} // End Default Constructor 


        // Parameterized Constructor (L-Value)
        MinHeap(const std::vector<Comparable>& elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");
            
            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (L-Value)


        // Parameterized Constructor (R-Value)
        MinHeap(std::vector<Comparable>&& elements)
        : current_size_(elements.size()), array_(MAX_SIZE + 1)
        {
            if (current_size_ > MAX_SIZE)
                throw std::out_of_range("Error: Number of elements exceed Heap size.\n");

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];
            
            heapify();
        } // End Parameterized Constructor (R-Value)


        // Copy Constructor
        MinHeap(const MinHeap &rhs) : current_size_(rhs.current_size_), array_(rhs.array_)
        {} // End Copy Constructor

        // Copy Assignment
        MinHeap& operator=(const MinHeap &rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            heapify();

            return *this;
        } // End Copy Assignment

        
        // Move Constructor
        MinHeap(MinHeap &&rhs)
        {
            current_size_ = rhs.current_size_;
            array_ = rhs.array_;

            rhs.current_size_ = 0;
        } // End Move Constructor

        
        // Move Assignment
        MinHeap& operator=(MinHeap &&rhs)
        {
            std::swap(current_size_, rhs.current_size_);
            std::swap(array_, rhs.array_);

            rhs.current_size_ = 0;

            return *this;
        } // End Move Assignment


        // Destructor 
        ~MinHeap()
        {
            current_size_ = 0;
        } // End Destructor


        // Assignment Overload
        MinHeap& operator=(const std::vector<Comparable> &elements)
        {
            current_size_ = elements.size();
            array_.resize(MAX_SIZE + 1);

            for (size_t i = 0; i < current_size_; i++)
                array_[i + 1] = elements[i];     
            heapify();

            return *this;
        } // End Assignment Overload


        void insert(const Comparable &new_item)
        {
            if (isFull())
                throw std::out_of_range("Heap is full, Unable to insert element.\n");
            
            int hole = ++current_size_;
            while (hole > 1 && new_item < array_[hole/2])
            {
                array_[hole] = array_[hole/2];
                hole = hole/2;
            }
            array_[hole] = new_item;
        }

        void deleteMin()
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty, No minimum element present.\n");

            array_[1] = array_[current_size_];
            current_size_--;
            percolateDown(1);
        }

        void heapify()
        {
            for (int i = current_size_ / 2; i > 0; i--)
                percolateDown(i);
        }

        int getMin() const
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty, No minimum element present.\n");

            return array_[1];
        }

        int getCurrentSize() const
        {
            return current_size_;
        }

        void display() const
        {
            for (size_t i = 1; i <= current_size_; i++)
            {
                std::cout << "Index[" << i << "]: " << array_[i];

                size_t left_child_index = 2 * i;
                size_t right_child_index = 2 * i + 1;

                if (left_child_index <= current_size_)
                {
                    std::cout << ", Left Child[" << left_child_index << "]: " << array_[left_child_index];
                }

                if (right_child_index <= current_size_)
                {
                    std::cout << ", Right Child[" << right_child_index << "]: " << array_[right_child_index];
                }

                std::cout << std::endl;
            }
            std::cout << std::endl;
        }


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
                if (child != current_size_ && array_[child + 1] < array_[child])
                    child++;
                
                if (array_[child] < temp)
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

#endif // MINHEAP_H