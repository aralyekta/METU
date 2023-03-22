#include "the3.h"

// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    n         : number of elements in the array
    l         : the number of characters used in counting sort at each time
    
    you can use ceil function from cmath
    
*/

// Use this to access the count array
// Remove this from the base26 of the biggest number with a smaller num of digits
// And also remove 1 to do array indexing
int base26(std::string str, int strLen, int numOfChars) {
    int number = 0;
    int power = 0;
    int j = strLen-1;
    for (; j >= 0; j--) {
        // std::cout << "Starting, j:" << j << "\n";
        char curChar = str[j];
        int orderOfChar = curChar - 'A' + 1; // We need to count A from 1, not 0
        // std::cout << "curChar: " << curChar << " and order of char: " << orderOfChar << "\n";
        if (orderOfChar < 0) {
            // This means it is erroneous
            std::cout << "Erroneous string, cant turn to base 26\n";
            return -1;
        }
        int coeff = pow(numOfChars, power);
        number += coeff * orderOfChar;
        // std::cout << "Finishing, j: " << j << "\n";
        power++;
    }
    return number;
}

// n is the length of str
int getIndexOfStr(std::string str, int n, int biggestLessDigitOrder, int numOfChars) {
    int orderOfStr = base26(str, n, numOfChars);
    return orderOfStr - biggestLessDigitOrder - 1;
}

int countingSort(std::string arr[], bool ascending, int n, int l, int startIndex) {
    int numOfChars = 'Z' - 'A' + 1;
    int totalSize = pow(numOfChars, l);
    int numOfIterations = 0;
    // End if the array is empty
    if (arr == nullptr || n <= 0) {
        return 0;
    }

    // Find the order in base26 of the biggest number which has less digits than l
    std::string biggestLessDigitStr;
    for (int i = 0; i < l-1; i++) {
        biggestLessDigitStr.append("Z");
    }
    // std::cout << "Calling base26 for:" << biggestLessDigitStr << "\n";
    int biggestLessDigitOrder = base26(biggestLessDigitStr, l-1, numOfChars);

    int *countArr = new int[totalSize]();
    // An example call
    // int indexToBeAccessed = getIndexOfStr(arr[0], sizeOfStrs, biggestLessDigitOrder, numOfChars);
    
    // Traverse the whole array and keep track of the number of occurrences.
    for (int i = 0; i < n; i++) {
        // std::cout << "start:" << startIndex << " and leng:" << l << " from " << arr[i] << "\n";
        std::string curStr = arr[i].substr(startIndex, l);
        // std::cout << "Calling for: " << curStr << "\n";
        int indexOfStr = getIndexOfStr(curStr, l, biggestLessDigitOrder, numOfChars);
        countArr[indexOfStr]++;
        numOfIterations++;
    }
    std::string *copyArr = new std::string[n];
    // std::cout << "Counted the elements\n";

    if (ascending) {
        // Add the number of occurrences to the right cumulatively
        for (int i = 0; i < totalSize - 1; i++) {
            countArr[i+1] += countArr[i];
            numOfIterations++;
        }
        numOfIterations++;

        // Traverse the string list from right to left to put them into their correct order
        // Put them in a copy list
        // Decrement the visited index by one each time (before accessing it)
        for (int i = n-1; i>= 0; i--) {
            std::string curSubstring = arr[i].substr(startIndex, l);
            // std::cout << "Calling for: " << curSubstring << " where curStr: " << arr[i] << "\n";
            int indexOfStr = getIndexOfStr(curSubstring, l, biggestLessDigitOrder, numOfChars);
            countArr[indexOfStr]--;
            int targetIndex = countArr[indexOfStr];
            // std::cout << "Targetindex is: " << targetIndex << "\n";
            copyArr[targetIndex] = arr[i];
            numOfIterations++;
        }
        // std::cout << "Loop is done\n";
        // Move the elements of the copy list back to the list given as argument
        for (int i = 0; i < n; i++) {
            arr[i] = copyArr[i];
            numOfIterations++;
        }
    }
    else {
        // Add the number of occurrences to the left cumulatively
        for (int i = totalSize-1; i > 0; i--) {
            countArr[i-1] += countArr[i];
            numOfIterations++;
        }
        numOfIterations++;
        // Shift the numbers to the left by one
        for (int i = 0; i < totalSize - 1; i++) {
            countArr[i] = countArr[i+1];
        }
        // Set the rightmost cell to 0, as it will belong to the first element of the sorted array
        countArr[totalSize-1] = 0;
        // Traverse the string list from left to right to put them into their correct order
        // Put them in a copy list
        // Increment the visited index by one each time
        for (int i = 0; i < n; i++) {
            std::string curSubstring = arr[i].substr(startIndex, l);
            // std::cout << "Calling for: " << curSubstring << " where curStr: " << arr[i] << "\n";
            int indexOfStr = getIndexOfStr(curSubstring, l, biggestLessDigitOrder, numOfChars);
            int targetIndex = countArr[indexOfStr];
            countArr[indexOfStr]++;
            copyArr[targetIndex] = arr[i];
            numOfIterations++;
        }
        // std::cout << "Loop is done\n";
        // Move the elements of the copy list back to the list given as argument
        for (int i = 0; i < n; i++) {
            arr[i] = copyArr[i];
            numOfIterations++;
        }
    }
    delete []countArr;
    delete []copyArr;
    return numOfIterations;
}

int radixSort(std::string arr[], bool ascending, int n, int l){
    int result = 0;
    if (arr == nullptr || n <= 0) {
        return 0;
    }
    int lenOfStrs = arr[0].size();
    // std::cout << lenOfStrs << "\n";
    int i = 1;
    while (lenOfStrs - i*l >= 0) {
        // std::cout << "Calling for l " << l << " and start index: " << (lenOfStrs - i*l) << "\n";
        result += countingSort(arr, ascending, n, l, (lenOfStrs - i*l));
        i++;
    }
    if (lenOfStrs - (i-1)*l == 0) {
        // If the start index of the previous iteration is 0
        // We dont need to invoke any method
    }
    else {
        // If the start index of the previous iteration is not 0, this means we skipped some beginning indices
        // std::cout << "Calling for l " << lenOfStrs - (i-1)*l << " and start index: " << 0 << "\n";
        result += countingSort(arr, ascending, n, lenOfStrs - (i-1)*l, 0);
    }
    return result;
}
