#include "the4.h"
#include <iostream>


int recursive_sln(int i, int* arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1;
    if (i == 0) {
        return arr[0];
    }
    else if (i == 1) {
        return arr[0] > arr[1] ? arr[0] : arr[1];
    }
    else if (i == 2) {
        int max1_2 = arr[0] > arr[1] ? arr[0] : arr[1];
        return arr[2] > max1_2 ? arr[2] : max1_2;
    }
    else {
        int prev3 = recursive_sln(i-3, arr, number_of_calls);
        int prev1 = recursive_sln(i-1, arr, number_of_calls);
        return prev3 + arr[i] > prev1 ? prev3 + arr[i] : prev1;  
    }
}



int memoization_sln(int i, int* arr, int* mem){ //memoization
    if (i == 0) {
        if (mem[0] == -1) {
            mem[0] = arr[0];
        }
        return mem[0];
    }
    else if (i == 1) {
        if (mem[0] == -1) {
            mem[0] = arr[0];
        }
        int val0 = mem[0];
        if (mem[1] == -1) {
            mem[1] = arr[1] > val0 ? arr[1] : val0; 
        }
        return mem[1];
    }
    else if (i == 2) {
        if (mem[0] == -1) {
            mem[0] = arr[0];
        }
        int val0 = mem[0];
        if (mem[1] == -1) {
            mem[1] = arr[1] > val0 ? arr[1] : val0;
        }
        int val1 = mem[1];
        if (mem[2] == -1) {
            mem[2] = arr[2] > val1 ? arr[2] : val1;
        }
        return mem[2];
    }
    else {
        int prev3 = memoization_sln(i-3, arr, mem);
        int prev1 = memoization_sln(i-1, arr, mem);
        mem[i] = prev3 + arr[i] > prev1 ? prev3 + arr[i] : prev1;
        return mem[i];  
    }
}



int dp_sln(int size, int* arr, int* mem){ //dynamic programming
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            mem[0] = arr[0];
        }
        else if (i == 1) {
            int val0 = mem[0];
            mem[1] = arr[1] > val0 ? arr[1] : val0;
        }
        else if (i == 2) {
            int val1 = mem[1];
            mem[2] = arr[2] > val1 ? arr[2] : val1;
        }
        else {
            int val3Before = mem[i-3];
            int val1Before = mem[i-1];
            mem[i] = val3Before + arr[i] > val1Before ? val3Before + arr[i] : val1Before;
        }
    }
    return mem[size-1];
}

