// Yzer De Gula 
// Few comments describing the class Points2D
/*
        The class Points2D hold a sequence of 2D points held in the stl array 
    data structure, denoted by the private data variable sequence_. sequence_
    is described by std::array<Object, 2>*sequence_, meaning that it is an 
    array that holds Object (int, double, float?, etc.) and 2 values 
    (the 2D Point). The size of the array is held by the private data variable
    size_.

*/

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
// ADDING A NEW COMMENT
namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D() : size_(0)
    {    
    }; // End Default Constructor


    // Copy-constructor.
    Points2D(const Points2D &rhs)
    {
       // Set size of this to the size of the other object 
       size_ = rhs.size_;
       // Dynamically allocate this object's sequence to the size of the other
       sequence_ = new std::array<Object, 2>[size_];

        // Set the points of this object to the other
       for (size_t i = 0; i < size_; i++)
       {
        sequence_[i] = rhs.sequence_[i];
       }
    }; // End Copy Constructor


    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs)
    {
        // Call the Copy-Constructor
        Points2D copy = rhs;
        // Swap the contents of THIS object with the one we want to copy
        std::swap(*this, copy);

        // Return this object, which now has the copied data
        return *this;
    }; // End Copy-Assignment


    // Move-constructor.
    Points2D(Points2D &&rhs)
    {
        // Set the private data members to that of the other
        size_ = rhs.size_;
        sequence_ = rhs.sequence_;

        // Reset the data members of the one we copied from
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;

    }; // End Move-Constructor


    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs)
    {
        // Clear any existing sequence in our object
        delete[] sequence_;

        // Swap the data members of this with the other
        std::swap(size_, rhs.size_);
        std::swap(sequence_, rhs.sequence_);

        // Reset the data members of the one we copied from
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;

        // Return THIS object
        return *this;
    }; // End Move-Assignment


    ~Points2D()
    {
        // Clear all the data members and deallocate the sequence
        size_ = 0;
        sequence_ = nullptr;
        delete[] sequence_;
    }; // End Destructor

    // End of big-five.  


    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) : sequence_(new std::array<Object, 2>[1]), size_(1)
    {
        // Use an initializer list to set the sequence and size to accomodate a singular point
        // Set the first point in our sequence to the point passed in
        sequence_[0] = item;
    } // End One-Parameter Constructor


    size_t size() const 
    {
        // Return the size_ var of the Object called
        return size_;
    } // End size


    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const 
    {
        /*I think we should first consider the edge cases for the overloaded 
        array index operator. It would be out of bounds if the location is 
        greater than the size_ of the sequence or negative.
        */

        // This handles the case where the location that is trying to be accessed 
        // is larger than the amount of points stored in the sequence or less than 0
        if (location >= size_ || location < 0)
        {
        // If encountered, display an error message and abort
        std::cerr << "ERROR (out-of-range)).\n";
        std::abort();
        }

        // Otherwise, return the location of the point within the sequence
        return sequence_[location];
    } // End Overloaded [] Operator


    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) 
    {
        /*Could have something similar to merge sort, it should perform the operation first, and check if 
          either the first or second sequence has any other values to inserted, and then add any remaining
          elements in the larger sequence. 
          order or value doesn't matter so it should just put the points into the sequence. */

        /*I think that we should perform the add operations using a for loop for the length of the smaller
          array. Adding c1.sequence_[i][0] + c2.sequence_[i][0] for the x-coord and c1.sequences_[i][1] +
          c2.sequence_[i][1] for the y-coord. After that, we would see if there are any points left in the 
          first array (meaning that the left array was larger), or if there are any points left in the 
          second array (meaning that the right array was larger). Or rather we can compare the size's of the
          arrays and iterate through the smaller one first, so we would not run into an out-of-bounds error.
          So that after we can just append the points from the larger sequence.*/

    // Find the smaller and larger sizes of the 2 sequences
    size_t smaller_size = std::min(c1.size_, c2.size_);
    size_t larger_size = std::max(c1.size_, c2.size_);

    // Object to store the sum
    Points2D<Object> sum;

    // Set the data members to that of the larger size
    sum.size_ = larger_size;
    sum.sequence_ = new std::array<Object, 2>[larger_size];

    // Iterate through the smaller size and calculate the sum of points
    for (size_t i = 0; i < smaller_size; i++) {
        sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
    }

    // If c1 is the larger sequence, copy the remaining points of c1 to the sum
    if (c1.size_ > c2.size_) {
        for (size_t i = smaller_size; i < larger_size; i++) {
            sum.sequence_[i][0] = c1.sequence_[i][0];
            sum.sequence_[i][1] = c1.sequence_[i][1];
        }
    }
    // If c2 has the larger sequence, copy the remaining points of c2 to the sum
    else if (c2.size_ > c1.size_) {
        for (size_t i = smaller_size; i < larger_size; i++) {
            sum.sequence_[i][0] = c2.sequence_[i][0];
            sum.sequence_[i][1] = c2.sequence_[i][1];
        }
    }

    // Return the sum 
    return sum;
    } // End Overloaded + Operator


    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) 
    {
        // If the sequence is empty,
        if (some_points.size_ == 0) 
        {
            // Return an empty point
            out << "().\n";
        }
        // If the sequence has only one point,
        else if (some_points.size_ == 1)
        {
            // Display that point ending with a period
            out << "(" << some_points.sequence_[0][0] << ", " << some_points.sequence_[0][1] << ").\n";
        }
        // If the sequence has more than one point,
        else
        {
            // Iterating through the entire sequence,
            for (size_t i = 0; i < some_points.size_; i++)
            {
                // Display the point 
                out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ")";
                
                // If the point isn't the last point,
                if (i < some_points.size_ - 2)
                {
                    // Seperate the point using a comma
                    out << ", ";
                }
                // If the point is the last point,
                else if (i == some_points.size_ - 2)
                {
                    // Seperate the last point from the sequence with ", and "
                    out << ", and ";
                }
                // After reading all the input
                else
                {
                    // Create a new line
                    out << ".\n";
                }
            }
        }
        return out;
    } // End Overloaded << Operator


    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) 
    {
        // Declare a size_t var to store our size
        size_t size;
        // Get the first value in our input stream
        in >> size;

        // If there is no input,
        if (!in)
        {
            // Display an error message and abort the program
            std::cerr << "ERROR.\n";
            std::abort();
        }

        // If the size is 0,
        if (size == 0)
        {
            // It's an empty sequence and set the data members accordingly
            std::cout << "().\n";
            some_points.size_ = 0;
            some_points.sequence_ = nullptr;
            return in;
        }

        // After checking for these cases, set the data members of our object to our size
        some_points.size_ = size;
        some_points.sequence_ = new std::array<Object, 2>[size];

        // Iterating through the size,
        // (This accounts for if there are more values than the amount of points size calls for)
        for (size_t i = 0; i < size; i++)
        {
            // If the input cannot populate a valid point
            if (!(in >> some_points.sequence_[i][0] >> some_points.sequence_[i][1]))
            {
                // Display an error message and deallocate the resources used
                std::cerr << "ERROR.\n";
                delete[] some_points.sequence_;
                some_points.sequence_ = nullptr;
                some_points.size_ = 0;
                std::abort();
            }
        }
        return in;
    } // End Overloaded >> Operator


  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_