#ifndef _DEQUE
#define _DEQUE

#include "DequeException.h"
#include <iostream>
using namespace std;

/*
A deque is a data structure consisting of a list of items, on which the following operations are possible:

push(x): Insert item x on the front end of the deque.
pop(): remove the front item from the deque and return it.
inject(x): Insert item x on the back end of the deque.
eject(): Remove the back item from the deque and return it.

Write the implementation of deque using a circular array.
*/


const int MAX_DEQUE = 100;

class Deque {
public:
    Deque();  // default constructor; copy constructor and destructor are supplied by the compiler

    bool isEmpty() const;	// Determines if deque is empty.
    void push(const int& newItem); // Adds an item to the front of a deque.
    int pop();		   // Removes and returns the front item of a deque.
    void inject(const int& newItem); // Adds an item to the back of a deque.
    int eject();      // Removes and returns the back item from the deque.

    bool isFull(); // Determines if deque is full.
    int getFront(); // Return front element of Deque
    int getBack(); // Return rear element of Deque

private:
    int items[MAX_DEQUE];  	// array of items
    int front;         		// index to front of deque
    int back;                // index to back of deque
};


Deque::Deque(){// default constructor
   front = 0;
   back = 0;
}

bool Deque::isFull() {
    bool returnVal = false;
    if ((back+1) % MAX_DEQUE == front % MAX_DEQUE)
    {
        returnVal = true;
    }
    return returnVal;
}

bool Deque::isEmpty() const {
    return (front % MAX_DEQUE == back % MAX_DEQUE);
}

int Deque::getFront() {
    if (!(this->isEmpty()))
    {
        return items[front];
    }
    else
    {
        return -1;
    }
}

int Deque::getBack() {
    if (!(this->isEmpty()))
    {
        return items[(back -1 + MAX_DEQUE) % MAX_DEQUE];
    }
    else
    {
        return -1;
    }
}

int Deque::pop() {
    if (!(this->isEmpty()))
    {
        int returnVal = items[front];
        front = (front+1 + MAX_DEQUE) % MAX_DEQUE;
        return returnVal;
    }
    else
    {
        return -1;
    }
}

void Deque::push(const int& newItem) {
    if (!(this->isFull()))
    {
        if (this->isEmpty())
        {
            items[front] = newItem;
            back = (back+1) % MAX_DEQUE;
        }
        else
        {
            front = (front-1 + MAX_DEQUE) % MAX_DEQUE;
            items[front] = newItem;
        }
    }
}


int Deque::eject() {
    int returnVal;
    if (!(this->isEmpty()))
    {
        back = (back-1 + MAX_DEQUE) % MAX_DEQUE;
        returnVal = items[back];
        return returnVal;
    }
    else
    {
        return -1;
    }
}

void Deque::inject(const int& newItem) {
    if (!(this->isFull()))
    {
        if (this->isEmpty())
        {
            push(newItem);
        }
        else
        {
            items[back] = newItem; 
            back = (back+1 + MAX_DEQUE) % MAX_DEQUE;  
        }
    }
}
#endif // _EXCEPTION

