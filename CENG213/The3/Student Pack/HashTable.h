#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template <class K, class T>
HashTable<K, T>::HashTable() {
    int newSize = NextCapacity(0);
    int i;
    _capacity = newSize;
    _size = 0;
    _table = new Bucket[newSize];
    for (i = 0; i < _capacity; i++)
    {
        _table[i].entries[0].Value = T();
        _table[i].entries[0].Active = false;
        _table[i].entries[0].Deleted = false;
        _table[i].entries[1].Value = T();
        _table[i].entries[1].Active = false;
        _table[i].entries[1].Deleted = false;
    }
}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    int i;
    _size = rhs._size;
    _capacity = rhs._capacity;
    _table = new Bucket[_capacity];
    for (i = 0; i < _capacity; i++)
    {
        _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
        _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
        _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
        _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
        _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
        _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
        _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
        _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
    }
}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    int i;
    delete [] _table;
    _size = rhs._size;
    _capacity = rhs._capacity;
    _table = new Bucket[_capacity];
    for (i = 0; i < _capacity; i++)
    {
        _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
        _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
        _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
        _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
        _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
        _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
        _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
        _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
    }
    return *this;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    delete [] _table;
}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    double loadFactor = (double)_size/(2*_capacity);
    Bucket *ptrToInsert;
    int i = 0;
    int hashedVal;
    if (loadFactor > 0.6)
    {
        Resize(NextCapacity(_capacity));
    }
    hashedVal = Hash(key);
    for (ptrToInsert = _table + (hashedVal % _capacity);
        (ptrToInsert->entries[0].Active || ptrToInsert->entries[0].Deleted) && 
        (ptrToInsert->entries[1].Active || ptrToInsert->entries[1].Deleted);
        i++, ptrToInsert = _table + ((hashedVal + i*i) % _capacity)
        )
        {
            if (ptrToInsert->entries[0].Active && ptrToInsert->entries[0].Key == key)
            {
                //Will be updated at 0
                break;
            }
            else if (ptrToInsert->entries[1].Active && ptrToInsert->entries[1].Key == key)
            {
                //Will be updated at 1
                break;
            }
        }
    if (ptrToInsert->entries[0].Active && ptrToInsert->entries[0].Key == key)
    {
        //Update with 0
        ptrToInsert->entries[0].Value = value;
    }
    else if (ptrToInsert->entries[1].Active && ptrToInsert->entries[1].Key == key)
    {
        //Update with 1
        ptrToInsert->entries[1].Value = value;
    }
    else if (!ptrToInsert->entries[0].Active)
    {
        //Insert at 0
        ptrToInsert->entries[0].Key = key;
        ptrToInsert->entries[0].Value = value;
        ptrToInsert->entries[0].Deleted = false;
        ptrToInsert->entries[0].Active = true;
        _size++;
    }
    else if (!ptrToInsert->entries[1].Active)
    {
        //Insert at 1
        ptrToInsert->entries[1].Key = key;
        ptrToInsert->entries[1].Value = value;
        ptrToInsert->entries[1].Deleted = false;
        ptrToInsert->entries[1].Active = true;
        _size++;
    }
}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    int hashVal = Hash(key), i;
    Bucket *ptrToDelete;
    for (ptrToDelete = _table + (hashVal % _capacity), i = 0;
    (ptrToDelete->entries[0].Deleted || ptrToDelete->entries[0].Active) &&
    (ptrToDelete->entries[1].Deleted || ptrToDelete->entries[1].Active);
    i++, ptrToDelete = _table + ((hashVal + i*i) % _capacity)
    )
    {
        if (ptrToDelete->entries[0].Active && ptrToDelete->entries[0].Key == key)
        {
            //Found the key to be deleted at 0
            break;
        }
        else if (ptrToDelete->entries[1].Active && ptrToDelete->entries[1].Key == key)
        {
            //Found the key to be deleted at 1
            break;
        }
    }
    if (ptrToDelete->entries[0].Active && ptrToDelete->entries[0].Key == key)
    {
        //Delete from 0
        ptrToDelete->entries[0].Deleted = true;
        ptrToDelete->entries[0].Active = false;
        _size--;
    }
    else if (ptrToDelete->entries[1].Active && ptrToDelete->entries[1].Key == key)
    {
        //Delete from 1
        ptrToDelete->entries[1].Deleted = true;
        ptrToDelete->entries[1].Active = false;
        _size--;
    }
    else
    {
        throw ItemNotFoundException();
    }
}

template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {    
    int hashVal = Hash(key), i;
    Bucket *ptrToGet;
    for (ptrToGet = _table + (hashVal % _capacity), i = 0;
    (ptrToGet->entries[0].Deleted || ptrToGet->entries[0].Active) &&
    (ptrToGet->entries[1].Deleted || ptrToGet->entries[1].Active);
    i++, ptrToGet = _table + ((hashVal + i*i) % _capacity)
    )
    {
        if (ptrToGet->entries[0].Active && ptrToGet->entries[0].Key == key)
        {
            //Found the key at 0
            break;
        }
        else if (ptrToGet->entries[1].Active && ptrToGet->entries[1].Key == key)
        {
            //Found the key at 1
            break;
        }
    }
    if (ptrToGet->entries[0].Active && ptrToGet->entries[0].Key == key)
    {
        //Found at 0
        return ptrToGet->entries[0].Value;
    }
    else if (ptrToGet->entries[1].Active && ptrToGet->entries[1].Key == key)
    {
        //Found at 1
        return ptrToGet->entries[1].Value;
    }
    else
    {
        throw ItemNotFoundException();
    }
}


template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    Bucket *oldTable = _table;
    int i, old_cap = _capacity;
    _capacity = newCapacity;
    _size = 0;
    _table = new Bucket[newCapacity];
    //Set all values to default
    for (i = 0; i < newCapacity; i++)
    {
        _table[i].entries[0].Value = T();
        _table[i].entries[0].Active = false;
        _table[i].entries[0].Deleted = false;
        _table[i].entries[1].Value = T();
        _table[i].entries[1].Active = false;
        _table[i].entries[1].Deleted = false;
    }
    //Rehash all the existing data
    for (i = 0; i < old_cap; i++)
    {
        if (oldTable[i].entries[0].Active)
        {
            Insert(oldTable[i].entries[0].Key, oldTable[i].entries[0].Value);
        }
        if (oldTable[i].entries[1].Active)
        {
            Insert(oldTable[i].entries[1].Key, oldTable[i].entries[1].Value);
        }
    }
    delete [] oldTable;
}


template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif