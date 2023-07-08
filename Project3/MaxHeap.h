#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <array>
#include <stdexcept>
#include <functional>

#define MAX_SIZE 100

// Max Heap Implementation
template <typename Comparable>
class MaxHeap
{
    public:
        MaxHeap() : current_size_(0)
        {
            for (int i = 0; i <= MAX_SIZE; i++)
            {
                array_[i] = Comparable();
            }      
        }

        MaxHeap(const std::array<Comparable, MAX_SIZE>& elements) : current_size_(elements.size())
        {
            if (current_size_ > MAX_SIZE)
            {
                throw std::out_of_range("Number of elements exceeds the maximum heap size.\n");
            }

            for (int i = 0; i < current_size_; i++)
            {
                array_[i + 1] = elements[i];
            }
            heapify();
        }


        void insert(const Comparable& new_item)
        {
            if (isFull())
            {
                throw std::logic_error("Heap is full, Unable to insert element.\n");
            }

                int hole = current_size_++;
                while (hole > 1 && new_item > array_[hole/2])
                {
                    array_[hole] = array_[hole/2];
                    hole = hole/2;
                }
            array_[hole] = new_item;
        }

        void deleteMax()
        {
            if (isEmpty())
            {
                throw std::logic_error("Heap is empty. No maximum element present.\n");
            }

            array_[1] = array_[current_size_];
            current_size_--;
            percolateDown(1);
        }

        void heapify()
        {
            for (int i = current_size_/2; i > 0; i--)
                percolateDown(i);
        }

        void percolateDown(int hole)
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

        bool isFull() const
        {
            return (current_size_ == MAX_SIZE);
        }

        bool isEmpty() const
        {
            return (current_size_ == 0);
        }

        Comparable getMax() const
        {
            if (isEmpty())
            {
                throw std::logic_error("Heap is empty. No maximum element present.\n");
            }

            return array_[1];
        }

        int getCurrentSize() const
        {
            return current_size_;
        }

        std::array<Comparable, MAX_SIZE + 1> getArray() const
        {
            return array_;
        }

    private:
        std::array<Comparable, MAX_SIZE + 1> array_;
        int current_size_;

};

#endif // MAXHEAP_H