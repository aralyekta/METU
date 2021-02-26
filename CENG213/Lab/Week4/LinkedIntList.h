#ifndef _LList
#define _LList

#include "ListNode.h"
#include "NoSuchElementException.h"

class LinkedIntList {
public:
    LinkedIntList() {
        front = NULL;
    }

    ~LinkedIntList();

    LinkedIntList(const LinkedIntList &rhs);

    LinkedIntList &operator=(const LinkedIntList rhs);

    void add(int value);

    void add(int index, int value);

    void addSorted(int value);

    int get(int index);

    int remove(); // throws NoSuchElementException;

    void remove(int index);

    void print();

    // TODO
    // Write a method called "set" that accepts an index and a value and
    // sets the list’s element at that index to have the given value.
    // You may assume that the index is between 0 (inclusive) and the size of the list (exclusive).
    void set(int index, int value);

    // TODO
    // Write a method called "min" that returns the minimum value in a list of integers.
    // If the list is empty, it should throw a NoSuchElementException.
    int min();

    // TODO
    // Write a method called "lastIndexOf" that accepts an integer value as a parameter and
    // that returns the index in the list of the last occurrence of that value or -1 if the value is not found in the list.
    // For example if a variable list stores values [1, 18, 2, 7, 18, 39, 18, 40] then the call of list.lastIndexOf(18)
    // should return 6. If the call instead is list.lastIndexOf(3), the method returns -1.
    int lastIndexOf(int value);

    // TODO
    // Write a method called "deleteBack" that deletes the last value (the value at the back of the list) and
    // returns the deleted value. If the list is empty, throw a NoSuchElementException.
    int deleteBack();

    // TODO
    // Write a method called "stretch" that takes an integer n as a parameter and that increases a list of integers
    // by a factor of n by replacing each integer in the original list with n copies of that integer.
    // For example if a variable called list stores [18, 7, 4, 24, 11] and we make the call of list.stretch(3);
    // the list should be changed to store [18, 18, 18, 7, 7, 7, 4, 4, 4, 24, 24, 24, 11, 11, 11].
    // If n is zero or negative the list should become empty.
    void stretch(int n);

    // TODO
    // Write a method called "removeAll" that removes all occurrences of a particular value.
    // For example if a variable list stores the values [3, 9, 4, 2, 3, 8, 17, 4, 3, 18], the call list.removeAll(3);
    // would change the list to store [9, 4, 2, 8, 17, 4, 18].
    void removeAll(int value);

    // TODO
    // Write a method called "equals" that accepts a second list as a parameter,
    // returns true if the two lists are equal, and returns false otherwise.
    // Two lists are considered equal if they store exactly the same values in exactly the same order and
    // have exactly the same length.
    bool equals(const LinkedIntList &L);

    // TODO
    // Write a method called "merge" that accepts a second list as a parameter.
    // This function adds the elements of the second list to the current one.
    // It creates new nodes with the values in second list and adds them into the first list.
    void merge(const LinkedIntList &L);

private:
    ListNode *front;
};

#endif
