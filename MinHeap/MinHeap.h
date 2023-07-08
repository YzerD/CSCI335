// Yzer De Gula
// MinHeap.h Template Class for a Min Heap

#ifndef MINHEAP_H
#define MINHEAP_H

#include <array>
#include <stdexcept>
#include <functional>
#include <iostream>



// Min Heap Implementation
template <typename Comparable>
class MinHeap
{
    public:
        MinHeap() : current_size_(0)
        {

        }


        void insert( const Comparable & new_item )
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
                throw std::out_of_range("Heap is empty. No maximum element present.\n");

            array_[1] = array_[current_size_];
            current_size_--;
            percolateDown(1);
        }

        void heapify()
        {
            for (int i = current_size_ / 2; i > 0; i--)
            {
                percolateDown(i);
            }
        }

        int getMin() const
        {
            if (isEmpty())
                throw std::out_of_range("Heap is empty. No maximum element present.\n");

            return array_[1];
        }

        int getCurrentSize() const
        {
            return current_size_;
        }

        void display() const
        {
            std::cout << "Array: " << std::endl;
            for (size_t i = 1; i <= current_size_; i++)
            {
                std::cout << "Array[" << i << "]: " << array_[i] << std::endl; 
            }
            std::cout << std::endl;
        }


    private:
        static const int MAX_SIZE = 100;
        Comparable array_[MAX_SIZE + 1];
        size_t current_size_;

        void percolateDown( int hole )
        {
            int child;
            Comparable temp = array_[hole];

            while (2*hole <= current_size_)
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