// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "the4.h"

int getRandomInt(){
        int r = rand()%100;
        return r;
}


void randomArray(int*& array, int size){
    array = new int [size];
    for (int i = 0; i < size; i++){
        int r = getRandomInt();
        array[i] = r;
    }
}


void printArrayInLine(int arr[], int arraySize){
        std::cout << "{ ";
        for(int i = 0; i < arraySize; i++){
                std::cout << arr[i];
        if (i == arraySize - 1){
            continue;
        }else{
            std::cout << ", ";
        }
        }
        std::cout << " }" << std::endl;
}



void test(){
    clock_t begin, end;
        double duration;
    int max_sum_rec;
        int max_sum_mem;
        int max_sum_dp;

    while (true) {
int size = rand() % 50;      // max 10000
    if (size == 0) {
        size++;
    }
    int* arr;
    randomArray(arr, size);
    // std::cout << "Array:" << std::endl;
    // printArrayInLine(arr, size);
    int *mem1 = new int[size];
    bool wrong = false;

        // std::cout << "_____________RECURSIVE IMPLEMENTATION:_____________" << std::endl;

    int number_of_calls_rec = 0;

    if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

        max_sum_rec = recursive_sln(size-1, arr, number_of_calls_rec);

    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    //     std::cout << "Duration: " << duration << " seconds." << std::endl;

    //     std::cout << "Max sum: " << max_sum_rec << std::endl;
    // std::cout << "Number of recursive calls: " << number_of_calls_rec << std::endl;

    //     std::cout << "---------------------------------------------------";
    //     std::cout << "\n" << std::endl;



        int* mem = new int[size];


        // std::cout << "______________________MEMOIZATION:__________________" << std::endl;

        for(int i = 0; i < size; i++) mem[i] = -1;


        if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    max_sum_mem = memoization_sln(size-1, arr, mem);
    for (int i = 0; i < size; i++) {
        mem1[i] = mem[i];
    }
    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
        // std::cout << "Duration: " << duration << " seconds." << std::endl;

        // std::cout << "Max sum: " << max_sum_mem << std::endl;
        // std::cout << "Final mem: " << std::endl;
        // printArrayInLine(mem, size);

        // std::cout << "----------------------------------------------------";
        // std::cout << "\n" << std::endl;




        // std::cout << "__________________DYNAMIC PROGRAMMING:______________" << std::endl;

        for(int i = 0; i < size; i++) mem[i] = -1;


    if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

        max_sum_dp = dp_sln(size, arr, mem);

    for (int i = 0; i < size; i++) {
        if (mem[i] != mem1[i]) {
            std::cout << "MEM DIFFERENT FOR INPUT: \n";
            printArrayInLine(arr, size);
            wrong = true;
        }
    }
    if (max_sum_dp != max_sum_mem || max_sum_dp != max_sum_rec || max_sum_mem != max_sum_rec) {
        wrong = true;
        std::cout << "WRONG RESULT FOR INPUT: \n";
        printArrayInLine(arr, size);
    }

    if (!wrong) {
        std::cout << "IT WAS CORRECT\n";
    }
    else {
        std::cout << "There was a problem, breaking\n";
        break;
    }
    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
        // std::cout << "Duration: " << duration << " seconds." << std::endl;

        // std::cout << "Max sum: " << max_sum_dp << std::endl;
        // std::cout << "Final mem: " << std::endl;
        // printArrayInLine(mem, size);

        // std::cout << "----------------------------------------------------";
        // std::cout << "\n" << std::endl;

    delete []mem1;
    }
    
}

int main()
{
    srandom(time(0));
    //test();
    int num = 0;
    int arr[] = {32, 51, 51, 92, 54, 90, 13, 69, 20, 6};
    int size = 10;
    int *mem = new int[size];
    for (int i = 0; i < size; i++) {
        mem[i] = -1;
    }
    std::cout << "Rec call: " << recursive_sln(size-1, arr, num) << "\n";
    std::cout << "Numof calls: " << num << "\n";
    std::cout << "Memoization: " << memoization_sln(size-1, arr, mem) << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << mem[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        mem[i] = -1;
    }
    std::cout << "DP: " << dp_sln(size, arr, mem) << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << mem[i] << " ";
    }
    std::cout << "\n";
    delete []mem;
    return 0;
}
