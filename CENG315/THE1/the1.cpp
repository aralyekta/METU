#include "the1.h"

//You can add your own helper functions

int sillySort(int* arr, long &comparison, long &swap, int size) 
{

    int num_of_calls=1;
	// [1,2]
	// [2,3]
	// [3,4]
	// [1,2]
	// [2,3]
	// [1,2]
	// Instead of allocating new arrays, we can set the start index and size to keep it in-place
	// size = 2^k
	// 0, 1, 2, 4, 8, 16, 32, 64, ...
	if (size < 4) {
		if (size == 2) {
			comparison++;
			if (arr[0] > arr[1]) {
				swap++;
				int temp = arr[0];
				arr[0] = arr[1];
				arr[1] = temp;
			}
		}
	}
	else {
		// [1,2]
		num_of_calls += sillySort(arr, comparison, swap, size/2);
		// [2,3]
		num_of_calls += sillySort(arr+size/4, comparison, swap, size/2);
		// [3,4]
		num_of_calls += sillySort(arr+size/2, comparison, swap, size/2);
		// [1,2]
		num_of_calls += sillySort(arr, comparison, swap, size/2);
		// [2,3]
		num_of_calls += sillySort(arr+size/4, comparison, swap, size/2);
		// [1,2]
		num_of_calls += sillySort(arr, comparison, swap, size/2);
	}
	return num_of_calls;
}


int crossMergeSort(int *arr, long &comparison, int size)
{
	// size = N = 2^k
	// 0, 1, 2, 4, 8, 16, 32, 64, ...
	int num_of_calls=1;
	
	if (size < 4) {
		if (size == 2) {
			comparison++;
			if (arr[0] > arr[1]) {
				int temp = arr[0];
				arr[0] = arr[1];
				arr[1] = temp;
			}
		}
	}
	else {
		// First quarter
		num_of_calls += crossMergeSort(arr, comparison, size/4);
		// Second quarter
		num_of_calls += crossMergeSort(arr+size/4, comparison, size/4);
		// Third quarter
		num_of_calls += crossMergeSort(arr+size/2, comparison, size/4);
		// Fourth quarter
		num_of_calls += crossMergeSort(arr+3*size/4, comparison, size/4);
		int *arr1 = new int[size/4];
		int *arr2 = new int[size/4];
		int *arr3 = new int[size/4];
		int *arr4 = new int[size/4];

		for (int i = 0; i < size/4; i++) {
			arr1[i] = arr[i];
			arr2[i] = arr[size/4+i];
			arr3[i] = arr[size/2+i];
			arr4[i] = arr[3*size/4+i];
		}

		int *h1 = new int[size/2];
		int *h2 = new int[size/2];

		int a = 0, b = 0, c = 0, d = 0;
		int h1Counter = 0, h2Counter = 0;
		while (a < size/4 && c < size/4) {
			comparison++;
			if (arr1[a] <= arr3[c]) {
				h1[h1Counter] = arr1[a];
				h1Counter++;
				a++;
			}
			else {
				h1[h1Counter] = arr3[c];
				h1Counter++;
				c++;
			}
		}
		if (a < size/4) {
			while (a < size/4) {
				h1[h1Counter] = arr1[a];
				h1Counter++;
				a++;
			}
		}
		else if (c < size/4) {
			while (c < size/4) {
				h1[h1Counter] = arr3[c];
				h1Counter++;
				c++;
			}
		}
		else {
			// I dont know what to do in this case, probably not possible
		}

		while (b < size/4 && d < size/4) {
			comparison++;
			if (arr2[b] <= arr4[d]) {
				h2[h2Counter] = arr2[b];
				h2Counter++;
				b++;
			}
			else {
				h2[h2Counter] = arr4[d];
				h2Counter++;
				d++;
			}
		}
		if (b < size/4) {
			while (b < size/4) {
				h2[h2Counter] = arr2[b];
				h2Counter++;
				b++;
			}
		}
		else if (d < size/4) {
			while (d < size/4) {
				h2[h2Counter] = arr4[d];
				h2Counter++;
				d++;
			}
		}
		else {
			// I dont know what to do in this case, probably not possible
		}

		h1Counter = 0;
		h2Counter = 0;
		int index = 0;
		while (h1Counter < size/2 && h2Counter < size/2) {
			comparison++;
			if (h1[h1Counter] <= h2[h2Counter]) {
				arr[index] = h1[h1Counter];
				index++;
				h1Counter++;
			}
			else {
				arr[index] = h2[h2Counter];
				index++;
				h2Counter++;
			}
		}
		if (h1Counter < size/2) {
			while (h1Counter < size/2) {
				arr[index] = h1[h1Counter];
				index++;
				h1Counter++;
			}
		}
		else if (h2Counter < size/2) {
			while (h2Counter < size/2) {
				arr[index] = h2[h2Counter];
				index++;
				h2Counter++;
			}
		}
		else {
			// I dont know what to do in this case, probably not possible
		}
		delete arr1;
		delete arr2;
		delete arr3;
		delete arr4;
	}
	return num_of_calls;
}