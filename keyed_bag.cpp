// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//
//
// INVARIANT for the keyed_bag class:
//   1. The number of items in the keyed_bag is in the member variable used;
//   2. For an empty keyed_bag, we do not care what is stored in any of data; for a
//      non-empty keyed_bag the items in the keyed_bag are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.

// coen 79 lab 4, keyed bag
// 2/1/23

#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include <iostream> // provide cout, endl
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    const keyed_bag::size_type keyed_bag::CAPACITY;

    // erase(key_type&) function O(n)
    // search for @param key in bag
    // if found, erase corresponding item, decrement 'used', swap last index to fill deleted entry, @return true
    // otherwise @return false
    bool keyed_bag::erase(const key_type& key) {
        // note: if bag is empty (used == 0) for loop does not run; O(1)
        for(size_type i=0; i<used; ++i) {
            if(keys[i] == key) {
                keys[i] = keys[--used];
                data[i] = data[used]; // 'used' decremented, last index of bag swapped to fill index (order doesnt matter)
                return true;
            }
        }
        return false;
    }

    // insert() function O(n)
    // throw exception if bag is already full, or if duplicate key
    // otherwise insert item into bag, increment count
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        try {
            if(used == CAPACITY) // throw exception if bag is full
                throw size_type(1);
            
            for(size_type i=0; i<used; ++i) // throw exception if duplicate key
                if(keys[i] == key)
                    throw size_type(2);
        } catch(size_type e) {
            if(e == 1)
                cout << "bag capacity exceeded. ";
            else
                cout << "duplicate key found. ";

            cout << "couldn't insert entry " << entry << " with key \"" << key << "\"" << endl;
            return;
        }

        keys[used] = key;
        data[used++] = entry; // increment 'used' and insert item to bag
    }

    // += operator O(n^2)
    // uses copy library functions
    // throw exception if added bags fill past capacity, or for duplicate key
    // otherwise combine @parameter addend to calling keyed_bag
    // @postcondition: used += addend.used
    void keyed_bag::operator +=(const keyed_bag& addend) {
        size_type duplicate; // initialized if duplicate key found
        try {
            if((used + addend.used) > CAPACITY) // throw exception if bags exceed capacity
                throw size_type(1);
            
            for(size_type i=0; i<addend.used; ++i) // iterate through keys of addend bag
                for(size_type j=0; j<used; ++j) // iterate through keys of bag (per key of addend bag) [O(n^2)]
                    if(keys[j] == addend.keys[i])
                        throw size_type(j); // throw index of duplicate key for exception handling

        } catch(size_type e) {
            if(e == 1)
                cout << "bag capacity exceeded. couldnt combine bags" << endl;
            else
                cout << "duplicate key \"" << keys[e] << "\" found. couldnt combine bags" << endl;
            
            return;
        }

        for(size_type i=0; i<addend.used; ++i) {
            keys[used] = addend.keys[i];
            data[used++] = addend.data[i]; // increment 'used', add items from addend to bag
        }
    }

    // has_key() function O(n)
    // @return true if @param key is in bag, false otherwise
    bool keyed_bag::has_key(const key_type& key) const {
        // note: if bag is empty (used == 0) for loop does not run; O(1)
        for(size_type i=0; i<used; ++i)
            if(keys[i] == key)
                return true;
        
        return false;
    }

    // get() function O(n)
    // @precondition: has_key() returns true (key is in the bag)
    // @return item given by @parameter key
    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
        try {
            if(!has_key(key)) {
                throw size_type(1);
            }
        } catch(size_type e) { // throw appropriate exception
                cout << "key is not in bag" << endl;
        }

        for(size_type i=0; i<used; ++i)
            if(keys[i] == key)
                return data[i];
    }

    // count() constant function O(n)
    // increment 'count' for each copy of @param target in bag
    // @return 'count'
    keyed_bag::size_type keyed_bag::count(const value_type& target) const
    {
        size_type count = 0;
        // note if bag is empty for loop does not run; O(1) in this case
        for(size_type i=0; i<used; ++i)
            if(data[i] == target)
                ++count;
        
        return count;
    }

    // + non-member operator O(n^2)
    // call += member operator with copy of @param b1, b2
    // @return 'b1a' which has b2a appended to it
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        keyed_bag b1a = b1;
        keyed_bag b2a = b2;
        b1a += b2a;
        return b1a;
    }

    // hasDuplicateKey() function O(n)
    // return true if duplicate key (using has_key() function)
    // return false otherwise
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        // note: if either bag is empty (used == 0 || otherBag.used == 0) for loop does not run; O(1)
        for(size_type i=0; i<otherBag.used; ++i)
            if(has_key(otherBag.keys[i]))
                return true;
        
        return false;
    }
}
