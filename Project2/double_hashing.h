#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

// Double Hashing Implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
    enum EntryType {ACTIVE, EMPTY, DELETED};
/******************************* START GETTERS *****************************/
    /**
        @return   : Return the total number of elements in the table (N)
    **/
    int getCurrentSize() const 
    {
        return current_size_;
    }

    /**
        @return   : Return the size of the table (T)
    **/
    int getTableSize() const
    {
        return array_.size();
    }

    /**
        @return   : Returns the load factor (N/T)
    **/
    float getLoadFactor() const
    {
        return (static_cast<float>(current_size_) / array_.size());
    }

    /**
        @return   : Returns the total number of collisions (C)
    **/
    int getCollisions() const
    {
        return collisions_;
    }

    /**
        @return   : Returns the average number of collisions (C/N)
    **/
    float getAverageCollisions()
    {
        return (static_cast<float>(collisions_) / array_.size());
    }

    /**
        @param    : A reference to an object in our Hash Table
        @return   : The number of probes it took to locate object's value
    **/
    int getNumberOfProbes(const HashedObj & x) const 
    {
        size_t current_pos = InternalHash(x);
        size_t offset = hash2(x);
        size_t probe_count = 1;
        
        while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) 
        {
        probe_count++;
        current_pos += offset;  // Compute ith probe.
        if (current_pos >= array_.size())
            current_pos -= array_.size();
        }
        return probe_count;
    }

/******************************** END GETTERS ******************************/
    /**
        @param    : Size of Hash Table
        @post     : The Hash Table is initialized with the given size (101 default)
                    and the underlying array is ensured to have a prime number 
                    greater than or eqaul to size to avoid collisions
    **/
    explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { 
        MakeEmpty(); 
    }
    
    /**
        @param    : The object to be checked if present in Hash Table
        @return   : Returns True if object is found in the Hash Table, false if not
    **/
    bool Contains(const HashedObj & x) const 
    {
        return IsActive(FindPos(x));
    }

    /**
        @post     : The Hash Table is emptied, and the current_size_ is set to 0
    **/
    void MakeEmpty() 
    {
        current_size_ = 0;
        for (auto &entry : array_)
        entry.info_ = EMPTY;
    }

    /**
        @param    : The object to be inserted (lvalue)
        @return   : Returns True if the insertion is successful, False otherwise
    **/
    bool Insert(const HashedObj & x)
    {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
        return false;
        
        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;
        
        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
        Rehash();    
        return true;
    }
    
    /**
        @param    : The object to be inserted (rvalue)
        @return   : Returns True if the insertion is successful, False otherwise
    **/
    bool Insert(HashedObj && x) {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
        return false;
        
        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;

        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
        Rehash();

        return true;
    }

    /**
        @param    : The object to be removed
        @return   : Returns True if object was found and deleted (lazy deletion),
                    and returns False otherwise.
    **/
    bool Remove(const HashedObj & x) {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
        return false;

        array_[current_pos].info_ = DELETED;
        return true;
    }

private:        
 struct HashEntry 
    {
        // Private data variables for HashEntry
        HashedObj element_;
        EntryType info_;
        
        /**
            @param    : Element of HashEntry (Default HashedObj)
            @param    : EntryType of HashEntry (Default EMPTY)
            @post     : Constructs a HashEntry with given values
        **/
        HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
        :element_{e}, info_{i} { }
        
        /**
            @param    : Rvalue element of HashEntry
            @param    : EntryType of HashEntry (Default EMPTY)
            @post     : Constructs a HashEntry with given values
        **/
        HashEntry(HashedObj && e, EntryType i = EMPTY)
        :element_{std::move(e)}, info_{ i } {}
    };
        
    // Private Data Variables for HashTableDouble
    std::vector<HashEntry> array_;
    size_t current_size_;
    mutable int collisions_ = 0;
    int R = 91;

    /**
        @param    : The position to check if ACTIVE
        @return   : Returns True if ACTIVE, False otherwise
    **/
    bool IsActive(size_t current_pos) const
    { 
        return array_[current_pos].info_ == ACTIVE; 
    }

    /**
        @param    : The element to search for (HashedObj)
        @return   : Retursn the positions of the element in our Hash Table
    **/
    size_t FindPos(const HashedObj & x) const {
        size_t current_pos = InternalHash(x);
        size_t offset = hash2(x);
        
        while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) 
        {
        collisions_++;
        current_pos += offset;  // Compute ith probe.
        if (current_pos >= array_.size())
            current_pos -= array_.size();
        }
        return current_pos;
    }

    /**
        @post     : Resizes the Hash Table by doubling if elements exceed
                    half of current size
    **/
    void Rehash() {
        std::vector<HashEntry> old_array = array_;

        // Create new double-sized, empty table.
        array_.resize(NextPrime(2 * old_array.size()));
        for (auto & entry : array_)
        entry.info_ = EMPTY;
        
        // Copy table over.
        current_size_ = 0;
        for (auto & entry :old_array)
        if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
    }
    
    /**
        @param    : The element which we want to compute Hash Index for
        @return   : The computed Hash Index
    **/
    size_t InternalHash(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size( );
    }

    /**
        @param    : The element which we want to compute Hash Index for
        @return   : The computed Hash Index with R
    **/
    size_t hash2(const HashedObj & x) const {
        static std::hash<HashedObj> hf;
        return R - (hf(x) % R);
    }

    // Internal method to test if a positive number is prime.
    /**
        @param    : The number to check if prime
        @return   : Returns True if prime, False otherwise
    **/
    bool IsPrime(size_t n) {
    if( n == 2 || n == 3 )
        return true;
    
    if( n == 1 || n % 2 == 0 )
        return false;
    
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
        return false;
    
    return true;
    }


    // Internal method to return a prime number at least as large as n.
    /**
        @param    : The number we want to find the next prime of
        @return   : The next prime number greater than or equal to param
    **/
    int NextPrime(size_t n) {
    if (n % 2 == 0)
        ++n;  
    while (!IsPrime(n)) n += 2;  
    return n;
    }    

};

#endif // DOUBLE_HASHING_H