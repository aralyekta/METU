// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include "the3.h"
#include <algorithm>

char getRandomChar(){
	return 'A' + (rand() % 26);
}

std::string getRandomString(int length){
	char* result_array = new char[length];
	for(int i = 0; i < length; i++){
		result_array[i] = getRandomChar();
	}
	std::string result(result_array, length);
	return result;
}

void randomArray(std::string*& array, int size, int length)
{
  array = new std::string[size];
  for (int i = 0; i < size; i++)
  {
    array[i] = getRandomString(length);
  }
}

void printArrayInLine(std::string arr[], int arraySize){
	std::cout << "{ ";
	for(int i = 0; i < arraySize; i++){
		std::cout << "\"" << arr[i] << "\"";
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
    int numberOfIterations;

  int size = rand() % 500;      // max 1000000
  int length = rand() % 13;     // max 12
  if (length == 0) {
    length++;
  }
  int l = rand() % 7;      // number of characters to be used in counting sort (1,2,3,4 or 6)
  if (l == 0) {
    l++;
  }
  else if (l == 5) {
    l++;
  }
  while (true) {
    std::string *arr;
    std::string *arr2 = new std::string[size];
    std::string *arr3 = new std::string[size];
    std::string *arr4 = new std::string[size];
    randomArray(arr, size, length);
    for (int i = 0; i < size; i++) {
      arr2[i] = arr[i];
      arr3[i] = arr[i];
    }
    int count1 = radixSort(arr, true, size, l);
    sort(arr2, arr2+size);
    for (int i = 0; i < size; i++) {
      arr4[i] = arr2[size - 1 - i];
    }
    int count2 = radixSort(arr3, false, size, l);
    bool error = false;
    for (int i = 0; i < size; i++) {
      if (arr[i] != arr2[i]) {
        std::cout << "ERROR at ascending sorting at index " << i << "\n";
        error = true;
        break;
      }
      if (arr3[i] != arr4[i]) {
        std::cout << "ERROR at descending sorting at index " << i << "\n";
        error = true;
        break;
      }
      if (count1 != count2) {
        std::cout << "ERROR at count numbers\n";
        error = true;
        break;
      }
    }
    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    if (!error) {
      std::cout << "Correct\n";
    }
  }
  


  //   std::cout << "Array before sorting:" << std::endl;
  //   printArrayInLine(arr, size);
  //   if ((begin = clock() ) ==-1)
	// 	std::cerr << "clock error" << std::endl;

  //   numberOfIterations = radixSort(arr, true, size, l);

  //   if ((end = clock() ) ==-1)
	// 	std::cerr << "clock error" << std::endl;

  //   duration = ((double) end - begin) / CLOCKS_PER_SEC;
	// std::cout << "Duration: " << duration << " seconds." << std::endl;

  //   std::cout << "Number of Iterations: " << numberOfIterations << std::endl;
  //   std::cout << "Array after sorting:" << std::endl;
  //   printArrayInLine(arr, size);

}

int main()
{
  srandom(time(0));
  test();
  // // std::string str[] = {"BAAA", "AABC", "CDBA", "CACB", "ABAB", "ACAB", "CBCB"};
  // // std::string str[] = { "AAA",  "ABA",  "ABC", "CCB" };
  // // std::string str[] = {"A", "A", "C", "B"};
  // // std::string str[] = {"BAAA", "AABC", "CDBA", "CACB", "ABAB", "ACAB", "CBCB"};
  // // std::string str[] = {"NWLRBBMQBHCD", "ARZOWKKYHIDD", "QSCDXRJMOWFR", "XSJYBLDBEFSA", "RCBYNECDYGGX", "XPKLORELLNMP", "APQFWKHOPKMC", "OQHNWNKUEWHS", "QMGBBUQCLJJI", "VSWMDKQTBXIX"};
  // // std::string str[] = {"AAAAAABAAAA", "AACAAAABAAA", "AACADAXAAAA", "AAAAAHAHAAA", "AAAAAFAAAAA", "AAAYASAAAAH"};
  // std::string str[] = {"NWLRBBMQBHCD", "ARZOWKKYHIDD", "QSCDXRJMOWFR", "XSJYBLDBEFSA", "RCBYNECDYGGX", "XPKLORELLNMP", "APQFWKHOPKMC", "OQHNWNKUEWHS", "QMGBBUQCLJJI", "VSWMDKQTBXIX"};
  // // std::string testStr = "asdasd";
  // int n = 10;
  // int l = 3;
  // bool ascending = false;
  // int numOfItr = radixSort(str, ascending, n, l);
	// std::cout << "# of iterations: " << numOfItr  << "\n";
  // // for (int i = 0; i < n; i++) {
  // //   std::cout << str[i] << " ";
  // // }
  // // std::cout << "\n";
  return 0;
}