#include <iostream>
#include "LinkedIntList.h"

using namespace std;

void LinkedIntList::add(int value) {
    if (front == NULL) {
        // adding to an empty list
        front = new ListNode(value);
    } else {
        // adding to the end of an existing list
        ListNode *current = front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new ListNode(value);
    }
}

void LinkedIntList::add(int index, int value) {
    if (index == 0) {
        // adding to an empty list
        front = new ListNode(value, front);
    } else {
        // inserting into an existing list
        ListNode *current = front;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        current->next = new ListNode(value, current->next);
    }
}

void LinkedIntList::addSorted(int value) {
    ListNode *current;
    if (front == NULL || front->data >= value) {
        // adding to an empty list
        front = new ListNode(value, front);
    } else {
        current = front;
        while (current->next && current->next->data < value) {
            current = current->next;
        }
        current->next = new ListNode(value, current->next);
    }
}


int LinkedIntList::get(int index) {
    ListNode *current = front;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int LinkedIntList::remove() {
    if (front == NULL) {
        throw NoSuchElementException();
    } else {
        int result = front->data;
        ListNode *tmp = front;
        front = front->next;
        delete tmp;
        return result;
    }
}

void LinkedIntList::remove(int index) {
    if (index == 0) {
        // special case: removing first element
        ListNode *tmp = front;
        front = front->next;
        delete tmp;
    } else {
        // removing from elsewhere in the list
        ListNode *current = front;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        ListNode *tmp = current->next;
        current->next = current->next->next;
        delete tmp;
    }
}

void LinkedIntList::print() {
    cout << "[ ";
    ListNode *current = front;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << "]" << endl;
}

LinkedIntList::~LinkedIntList() {
    while (front)
        remove();
}

LinkedIntList::LinkedIntList(const LinkedIntList &rhs) {
    front = NULL;
    *this = rhs; // use operator=
}

LinkedIntList &LinkedIntList::operator=(const LinkedIntList rhs) {
    if (this != &rhs) {
        while (front)
            remove();
        ListNode *r = rhs.front;

        while (r) {
            add(r->data);
            r = r->next;
        }
    }
    return *this;
}

// Write a method called "set" that accepts an index and a value and
// sets the list’s element at that index to have the given value.
// You may assume that the index is between 0 (inclusive) and the size of the list (exclusive).
void LinkedIntList::set(int index, int value) {
    int i;
    ListNode *ptr = front;
    for (i = 0; i < index; i++)
    {
        ptr = ptr->next;
    }
    ptr->data = value;
}

// Write a method called "min" that returns the minimum value in a list of integers.
// If the list is empty, it should throw a NoSuchElementException.
int LinkedIntList::min() {
    int min;
    ListNode *ptr = front;
    if (!ptr)
    {
        throw NoSuchElementException();
    }
    else
    {
        min = front->data;
        while (ptr)
        {
            ptr = ptr->next;
            if (ptr && ptr->data < min)
            {
                min = ptr->data;
            }
        }
        return min;
    }
}

// Write a method called "lastIndexOf" that accepts an integer value as a parameter and
// that returns the index in the list of the last occurrence of that value or -1 if the value is not found in the list.
// For example if a variable list stores values [1, 18, 2, 7, 18, 39, 18, 40] then the call of list.lastIndexOf(18)
// should return 6. If the call instead is list.lastIndexOf(3), the method returns -1.
int LinkedIntList::lastIndexOf(int value) {
    int result = -1, counter = 0;
    ListNode *ptr = front;
    while (ptr)
    {
        if (ptr->data == value)
        {
            result = counter;
        }
        ptr = ptr->next;
        counter++;
    }
    return result;
}

// Write a method called "deleteBack" that deletes the last value (the value at the back of the list) and
// returns the deleted value. If the list is empty, throw a NoSuchElementException.
int LinkedIntList::deleteBack() {
    int return_val;
    ListNode *ptr = front, *temp;
    if (!ptr)
    {
        throw NoSuchElementException();
    }
    else
    {
        if (!(ptr->next))
        {
            return_val = front->data;
            delete front;
            front = NULL;
        }
        else
        {
            while (ptr->next->next)
            {
                ptr = ptr->next;
            }
            temp = ptr->next;
            return_val = temp->data;
            ptr->next = temp->next;
            delete temp;
        }
        return return_val;
    }
}

// Write a method called "stretch" that takes an integer n as a parameter and that increases a list of integers
// by a factor of n by replacing each integer in the original list with n copies of that integer.
// For example if a variable called list stores [18, 7, 4, 24, 11] and we make the call of list.stretch(3);
// the list should be changed to store [18, 18, 18, 7, 7, 7, 4, 4, 4, 24, 24, 24, 11, 11, 11].
// If n is zero or negative the list should become empty.
void LinkedIntList::stretch(int n) {
    int currentIndex = 0, i, currentVal;
    ListNode *currPtr = front, *temp;
    if (n <= 0)
    {
        while(front)
        {
            remove();
        }
    }
    else if (n >= 2)
    {
        while(currPtr)
        {
            currentVal = currPtr->data;
            for (i = 0; i < n-1; i++)
            {
                temp = currPtr->next;
                ListNode *newNode = new ListNode(currentVal, temp);
                currPtr->next = newNode;
                currentIndex++;
                currPtr = currPtr->next;
            }
            currPtr = currPtr->next;
            currentIndex++;
        }
    }
}

// Write a method called "removeAll" that removes all occurrences of a particular value.
// For example if a variable list stores the values [3, 9, 4, 2, 3, 8, 17, 4, 3, 18], the call list.removeAll(3);
// would change the list to store [9, 4, 2, 8, 17, 4, 18].
void LinkedIntList::removeAll(int value) {
    ListNode *ptr = front, *temp;
    while (ptr)
    {
        while (ptr->next && ptr->next->data == value)
        {
            temp = ptr->next;
            ptr->next = temp->next;
            delete temp;
        }
        ptr = ptr->next;
    }
    if (front && front->data == value)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

// Write a method called "equals" that accepts a second list as a parameter,
// returns true if the two lists are equal, and returns false otherwise.
// Two lists are considered equal if they store exactly the same values in exactly the same order and
// have exactly the same length.
bool LinkedIntList::equals(const LinkedIntList &L) {
    ListNode *ptr = front, *ptr2 = L.front;
    while (ptr && ptr2)
    {
        if (ptr->data != ptr2->data)
        {
            return false;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    if (ptr || ptr2)
    {
        return false;
    }
    return true;
}

// Write a method called "merge" that accepts a second list as a parameter.
// This function adds the elements of the second list to the current one.
// It creates new nodes with the values in second list and adds them into the first list.
void LinkedIntList::merge(const LinkedIntList &L) {
    ListNode *ptr = front, *ptr2 = L.front;
    int currVal;
    while (ptr)
    {
        if (ptr->next)
        {
            ptr = ptr->next;
        }
        else
        {
            break;
        }
    }
    while (ptr2)
    {
        currVal = ptr2->data;
        ListNode *newNode = new ListNode(currVal, NULL);
        ptr->next = newNode;
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
}

int main()
{
    LinkedIntList deneme, deneme2 = deneme;
    return 0;
}