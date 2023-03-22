#include "the2.h"

//You may write your own helper functions here

void swapHelper(unsigned short *array, int i, int j, long &swap, double &avg_dist, double &max_dist) {
    // Set swap
    // Set avg_dist
    // Set max_dist
    int abs_dist = i-j>=0 ? i-j : j-i;
    double total_dist = avg_dist * swap;
    swap++;
    if (abs_dist > max_dist) {
        max_dist = abs_dist;
    } 
    total_dist += abs_dist;
    avg_dist = total_dist / swap;
    unsigned short temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int partition(unsigned short *arr, int size, long &swap, double &avg_dist, double &max_dist) {
    unsigned short pivot = arr[size-1];
    int i = -1;
    for (int j = 0; j < size-1; j++) {
        if (arr[j] >= pivot) {
            i++;
            swapHelper(arr, i, j, swap, avg_dist, max_dist);
        }
    }
    swapHelper(arr, i+1, size-1, swap, avg_dist, max_dist);
    return i+1;
}

int hoareHelper(unsigned short *arr, long &swap, double &avg_dist, double &max_dist, int size) {
    unsigned short pivot = arr[(size-1)/2];
    int i = -1;
    int j = size;
    while (true) {
        do {
            j--;
        } while(arr[j] < pivot);
        do {
            i++;
        } while(arr[i] > pivot);
        if (i<j) {
            swapHelper(arr, i, j, swap, avg_dist, max_dist);
        }
        else {
            // j is the location of the pivot
            return j;
        }
    }
}

void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size)
{
    if (!hoare) {
        // Partition
        if (size > 1) {
            int index = partition(arr, size, swap, avg_dist, max_dist);
            quickSort(arr, swap, avg_dist, max_dist, hoare, index);
            quickSort(arr+index+1, swap, avg_dist, max_dist, hoare, size-(index+1));
        }
    }
    else {
        // Hoare
        if (size > 1) {
            int p = hoareHelper(arr, swap, avg_dist, max_dist, size);
            quickSort(arr, swap, avg_dist, max_dist, hoare, p+1);
            quickSort(arr+(p+1), swap, avg_dist, max_dist, hoare, size-(p+1));
        }
    }
}

int *partition3(unsigned short *arr, long &swap, long &comparison, int size) {
    int i = 0;
    int j = 0;
    int p = size - 1;
    int *result = new int[2]; // Don't forget to delete this
    // These two are unnecessary
    double avg_dist = 0;
    double max_dist = 0;
    while (i < p) {
        bool comparedExtra = false;
        comparison++;
        if (arr[i] > arr[size-1]) {
            swapHelper(arr, i, j, swap, avg_dist, max_dist);
            i++;
            j++;
        }
        else if (arr[i] == arr[size-1]) {
            p--;
            comparedExtra = true;
            swapHelper(arr, i, p, swap, avg_dist, max_dist);
        }
        else {
            comparedExtra = true;
            i++;
        }
        if (comparedExtra) {
            comparison++;
        }
    }
    int m = p-j < size-p ? p-j : size-p;
    int startIndex1 = j;
    int endIndex1 = j+m; // Not inclusive
    int startIndex2 = size-m;
    int endIndex2 = size; // Not inclusive
    for (; startIndex1 < endIndex1 && startIndex2 < endIndex2; startIndex1++, startIndex2++) {
        swapHelper(arr, startIndex1, startIndex2, swap, avg_dist, max_dist);
    }
    result[0] = j;
    result[1] = p-j;
    return result;
}

void quickSort3(unsigned short *arr, long &swap, long &comparison, int size) {
	if (size > 1) {
        int *LR = partition3(arr, swap, comparison, size);
        int L = LR[0];
        int R = LR[1];
        delete [] LR;
        if (L > 0) {
            //std::cout << "Will call for " << arr[0] << " and final element:" << arr[L-1] << "\n";
            quickSort3(arr, swap, comparison, L);
        }
        if (R > 0) {
            quickSort3(arr+(size-R), swap, comparison, R);
            //std::cout << "Will call for " << arr[1+L] << " and final element:" << arr[R-1] << "\n";
        }
    }
}