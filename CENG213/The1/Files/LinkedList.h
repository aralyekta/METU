#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    int i;
    head = nullptr;
    tail = nullptr;
    Node<T> *newNode;
    for (i = 0; i < arrSize; i++)
    {
        if (i == 0)
        {
            newNode = new Node<T>(arr[i], nullptr, nullptr);
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode = new Node<T>(arr[i], tail, nullptr);
            tail->next = newNode;
            tail = tail->next;
        }
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    Node<T> *newNode, *ptr2 = obj.head;
    int i = 0;
    T currData;
    head = nullptr;
    tail = nullptr;
    while (ptr2)
    {
        currData = ptr2->data;
        if (i == 0)
        {
            newNode = new Node<T>(currData, nullptr, nullptr);
            head = newNode;
            tail = newNode;
            i++;
        }
        else
        {
            newNode = new Node<T>(currData, tail, nullptr);
            tail->next = newNode;
            tail = tail->next;
            i++;
        }
        ptr2 = ptr2->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> *currPtr = head, *temp;
    while (currPtr)
    {
        temp = currPtr;
        currPtr = currPtr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    return tail;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *currPtr = head;
    while (currPtr)
    {
        if (currPtr->data == data)
        {
            return currPtr;
        }
        currPtr = currPtr->next;
    }
    return currPtr;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    Node<T> *currPtr = head;
    int numOfNodes = 0;
    while (currPtr)
    {
        numOfNodes++;
        currPtr = currPtr->next;
    }
    return numOfNodes;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return (head == nullptr);
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> *currPtr = head;
    while (currPtr)
    {
        if (currPtr == node)
        {
            return true;
        }
        currPtr = currPtr->next;
    }
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
    Node<T> *newNode = new Node<T>(data, nullptr, head);
    if (head)
    {
        head->prev = newNode;
        head = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }
}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    Node<T> *newNode = new Node<T>(data, tail, nullptr);
    if (tail)
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }
}

template<class T>
void LinkedList<T>::insertSorted(const T &data) {
    Node<T> *currPtr = head, *newNode, *temp;
    while (currPtr)
    {
        if (currPtr->data > data)
        {
            break;
        }
        currPtr = currPtr->next;
    }
    if (currPtr == head)
    {
        insertAtTheHead(data);
    }
    else if (currPtr == nullptr)
    {
        insertAtTheTail(data);
    }
    else
    {
        temp = currPtr->prev;
        newNode = new Node<T>(data, temp, currPtr);
        currPtr->prev = newNode;
        temp->next = newNode;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    Node<T> *currPtr = head, *temp, *temp2;
    while (currPtr)
    {
        if (currPtr == node)
        {
            break;
        }
        currPtr = currPtr->next;
    }
    if (currPtr)
    {
        if (currPtr == head)
        {
            temp = currPtr->next;
            if (temp)
            {
                temp->prev = nullptr;
                delete head;
                head = temp;
            }
            else
            {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
        }
        else if (currPtr == tail)
        {
            temp = currPtr->prev;
            if (temp)
            {
                temp->next = nullptr;
                delete tail;
                tail = temp;
            }
            else
            {
                delete tail;
                head = nullptr;
                tail = nullptr;
            }
        }
        else
        {
            temp = currPtr->prev;
            temp2 = currPtr->next;
            temp->next = temp2;
            temp2->prev = temp;
            delete currPtr;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    Node<T> *currPtr = head, *temp, *temp2;
    while (currPtr)
    {
        if (currPtr->data == data)
        {
            break;
        }
        currPtr = currPtr->next;
    }
    if (currPtr)
    {
        if (currPtr == head)
        {
            temp = currPtr->next;
            if (temp)
            {
                temp->prev = nullptr;
                delete head;
                head = temp;
            }
            else
            {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
        }
        else if (currPtr == tail)
        {
            temp = currPtr->prev;
            if (temp)
            {
                temp->next = nullptr;
                delete tail;
                tail = temp;
            }
            else
            {
                delete tail;
                head = nullptr;
                tail = nullptr;
            }
        }
        else if (currPtr)
        {
            temp = currPtr->prev;
            temp2 = currPtr->next;
            temp->next = temp2;
            temp2->prev = temp;
            delete currPtr;
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    Node<T> *currPtr = head, *temp;
    while (currPtr)
    {
        temp = currPtr;
        currPtr = currPtr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const {
    int size = getNumberOfNodes(), i;
    T *arrayPtr;
    Node<T> *currPtr = head;
    if (size == 0)
    {
        return nullptr;
    }
    else
    {
        arrayPtr = new T[size];
        for (i = 0; i < size; i++)
        {
            arrayPtr[i] = currPtr->data;
            currPtr = currPtr->next;
        }
        return arrayPtr;
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    if (&rhs == this)
    {
        return (*this);
    }
    else
    {
        Node<T> *ptr2 = rhs.head;
        removeAllNodes();
        while (ptr2)
        {
            insertAtTheTail(ptr2->data);
            ptr2 = ptr2->next;
        }
        return (*this);
    }
}


#endif //LINKEDLIST_H
