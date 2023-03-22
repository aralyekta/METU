#ifndef _THE_3_H_
#define _THE_3_H_

#include <iostream>
#include <climits>
#include <cmath>
#include <string>

int base26(std::string str, int strLen, int numOfChars);

int countingSort(std::string arr[], bool ascending, int n, int l, int startIndex);

int radixSort(std::string arr[], bool ascending, int n, int l);

#endif