#ifndef _HTABLE
#define _HTABLE
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#define REMOVED "XXX"
using namespace std;

class HashStringTable{
public:
    // constructor that initializes the elements as a vector of size 11
    // with "" values.It also initializes oher private data members
    HashStringTable();

    // Adds string value to elements. It first checks the load factor.
    // If the load factor of elements is >=0.75 then its size is doubled and
    // all data are rehashed. During insertion duplicate values are ignored
    // (i.e. they are not added to the hash table)
    void add(string value) ;

    // returns the size of the hash table (i.e. vector elements)
    int get_size();

    //returns the number of data values in the hash table
    int get_count();

    //returns the average number of probes for successful search
    double get_avgProbe();

    // returns the average number of probes for unsuccessful search
    double get_unsuccessProbe();

    // returns true if the string value is in the hash table; false otherwise
    bool contains(string value);

    // returns true if value is removed successfully from the hash table; false otherwise
    // For the deleted items, you should use the "REMOVED" macro.
    bool remove(string value);

private:
    vector<string> elements; // the hash table implemented as a vector
    int cnt;	//current number of items in the table

    int total_probes;   //total number of probes that helps calculating the
    //average number of probes for successful search.


    // Hash function that finds the hash code corresponding to string str.
    // It should map the given string to an integer value between 0 and
    // hash table size -1.
    // Make sure that your hash function uses all characters of the string in
    // the computation.
    int hashcode(string str);

    // resizes the hash table by doubling its size. The new size will be
    //(oldsize*2)+1
    void rehash() ;

}; //end of class HashStringTable

HashStringTable::HashStringTable() {
    elements.resize(11,"");
    cnt = 0;
    total_probes = 0;
}

void HashStringTable::add(string value) {
  cout << "Successful: " << get_avgProbe() << "\n";
  cout << "Unsuccessful: " << get_unsuccessProbe() << "\n";
  int hashed_val, i;
  int vec_size = get_size();
  if (!contains(value))
  {
    if ((double)cnt/vec_size >= 0.75)
    {
      rehash();
      vec_size = get_size();
      for (i = 0, hashed_val = hashcode(value); elements[((hashed_val + i) % vec_size)] != "" && elements[((hashed_val + i) % vec_size)] != REMOVED; i++, total_probes++);
      elements[((hashed_val + i) % vec_size)] = value;
      total_probes++;
      cnt++;
    }
    else
    {
      for (i = 0, hashed_val = hashcode(value); elements[((hashed_val + i) % vec_size)] != "" && elements[((hashed_val + i) % vec_size)] != REMOVED; i++, total_probes++);
      elements[((hashed_val + i) % vec_size)] = value;
      total_probes++;
      cnt++;
    }
  }
}

int HashStringTable::get_size() {
    return elements.size();
}

int HashStringTable::get_count() {
    return cnt;
}

double HashStringTable::get_avgProbe() {
    return (cnt == 0)?1:(double)total_probes/(double)cnt;
}

double HashStringTable::get_unsuccessProbe() {
  int cur_size = get_size();
  int i, j, total_uns_probe = 0;
  for (i = 0; i < cur_size; i++)
  {
    for (j = 0; elements[(i+j) % cur_size] != ""; j++,total_uns_probe++);
    total_uns_probe++;
  }
  return (double)total_uns_probe/cur_size;
}

bool HashStringTable::contains(string value) {
  int hash_val = hashcode(value);
  int i, cur_size = get_size();
  for (i = 0; elements[((hash_val + i) % cur_size)] != ""; i++)
  {
    if (elements[((hash_val + i) % cur_size)] == value)
    {
      return true;
    }
  }
  return false;
}

bool HashStringTable::remove(string value) {
  int cur_size = get_size();
  int i, hash_val = hashcode(value);
  int probe_amount = 1;
  for (i = 0; elements[(hash_val+i)%cur_size] != "" && elements[(hash_val+i)%cur_size] != value; i++, probe_amount++);
  if (elements[(hash_val+i)%cur_size] == "")
  {
    return false;    
  }
  else
  {
    elements[(hash_val+i)%cur_size] = REMOVED;
    total_probes -= probe_amount;
    cnt--;
    return true;
  }
}

int HashStringTable::hashcode(string str) {
    int h = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        h = 31 * h + str[i];
    }
    h %= elements.size();
    if (h < 0)   /* in case overflows occurs */
        h += elements.size();

    return h;
}

void HashStringTable::rehash() {
  vector<string> handle = elements;
  int i, j, hashed_val;
  int prev_size = get_size();
  int new_size = 2 * prev_size + 1;
  string cur_elem;
  elements.clear();
  elements.resize(new_size, "");
  total_probes = 0;
  for (i = 0; i < prev_size; i++)
  {
    cur_elem = handle[i];
    if (cur_elem != "" && cur_elem != REMOVED)
    {
      hashed_val = hashcode(cur_elem);
      for (j = 0; elements[((hashed_val + j) % new_size)] != ""; j++, total_probes++)
      {
      }
      elements[((hashed_val + j) % new_size)] = cur_elem;
      total_probes++;
    }
  }
}


#endif // _HTABLE

