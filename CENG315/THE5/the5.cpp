#include "the5.h"
// do not add extra libraries here

#include <cstdio>

/*
W: the width of the field
L: the length of the field
partitions: 2D Boolean array for partitions, if a partition of w x l exists then partitions[x][y] is true.
numberOfCalls/numberOfIterations: method specific control parameter
*/

int recursiveMethod(int W, int L, bool** partitions, int* numberOfCalls){
	(*numberOfCalls)++;
	if (partitions[W][L] == true) {
		return 0;
	}
	int divideW = -1;
	int divideL = -1;
	int direct = W*L;
	int min = 0;
	for (int i = 1; i <= W/2; i++) {
		int result = recursiveMethod(W-i, L, partitions, numberOfCalls) + recursiveMethod(i, L, partitions, numberOfCalls);
		if (i == 1 || result < divideW) {
			divideW = result;
		}
	}
	for (int i = 1; i <= L/2; i++) {
		int result = recursiveMethod(W, L-i, partitions, numberOfCalls) + recursiveMethod(W, i, partitions, numberOfCalls);
		if (i == 1 || result < divideL) {
			divideL = result;
		}
	}
	if (divideW != -1 && divideL != -1) {
		int minDivide = divideW < divideL ? divideW : divideL;
		min = minDivide < direct ? minDivide : direct;
	}
	else if (divideW != -1) {
		// divideL = -1
		int minDivide = divideW;
		min = minDivide < direct ? minDivide : direct;	
	}
	else if (divideL != -1) {
		// divideW = -1
		int minDivide = divideL;
		min = minDivide < direct ? minDivide : direct;	
	}
	else {
		// Both of them are -1
		min = direct;
	}
	return min;
}

int memoizationHelper(int W, int L, bool** partitions, int* numberOfCalls, int** memArray) {
	(*numberOfCalls)++;
	if (memArray[W][L] != -1) {
		return memArray[W][L];
	}
	if (partitions[W][L] == true) {
		memArray[W][L] = 0;
		return memArray[W][L];
	}
	int divideW = -1;
	int divideL = -1;
	int direct = W*L;
	int min = 0;
	for (int i = 1; i <= W/2; i++) {
		int result = memoizationHelper(W-i, L, partitions, numberOfCalls, memArray) + memoizationHelper(i, L, partitions, numberOfCalls, memArray);
		if (i == 1 || result < divideW) {
			divideW = result;
		}
	}
	for (int i = 1; i <= L/2; i++) {
		int result = memoizationHelper(W, L-i, partitions, numberOfCalls, memArray) + memoizationHelper(W, i, partitions, numberOfCalls, memArray);
		if (i == 1 || result < divideL) {
			divideL = result;
		}
	}
	if (divideW != -1 && divideL != -1) {
		int minDivide = divideW < divideL ? divideW : divideL;
		min = minDivide < direct ? minDivide : direct;
	}
	else if (divideW != -1) {
		// divideL = -1
		int minDivide = divideW;
		min = minDivide < direct ? minDivide : direct;	
	}
	else if (divideL != -1) {
		// divideW = -1
		int minDivide = divideL;
		min = minDivide < direct ? minDivide : direct;	
	}
	else {
		// Both of them are -1
		min = direct;
	}
	memArray[W][L] = min;
	return memArray[W][L];
}

int memoizationMethod(int W, int L, bool** partitions, int* numberOfCalls){
	(*numberOfCalls)++; // I had to add this, but this is probably wrong.
	int** memArray = new int*[W+1];
	for (int i = 0; i < W+1; i++) {
		memArray[i] = new int[L+1];
	}
	for (int i = 0; i < W+1; i++) {
		for (int j = 0; j < L+1; j++) {
			memArray[i][j] = -1;
		}
	}
	int result = memoizationHelper(W, L, partitions, numberOfCalls, memArray);
	for (int i = 0; i < W+1; i++) {
		delete[] memArray[i];
	}
	delete[] memArray;
	return result;
}

int bottomUpMethod(int W, int L, bool** partitions, int* numberOfIterations){
	int** memArray = new int*[W+1];
	for (int i = 0; i < W+1; i++) {
		memArray[i] = new int[L+1];
	}

	for (int i = 0; i < W+1; i++) {
		for (int j = 0; j < L+1; j++) {
			memArray[i][j] = 0;
		}
	}

	for (int i = 1; i <= W; i++) {
		for (int j = 1; j <= L; j++) {
			
			if (partitions[i][j] == true) {
				memArray[i][j] = 0;
				continue;
			}
			int min = 0;
			int direct = i*j;
			int divW = -1;
			int divL = -1;
			for (int M = 1; M <= i; M++) {
				(*numberOfIterations)++;
				if (i-M <= 0) {
					continue;
				}
				int result = memArray[i-M][j] + memArray[M][j];
				// printf("AccessedM: [%d][%d]%d, [%d][%d]%d\n", i-M, j, memArray[i-M][j], i, j, memArray[i][j]);
				if (M == 1 || result < divW) {
					divW = result;
				}
			}
			for (int N = 1; N <= j; N++) {
				(*numberOfIterations)++;
				if (j-N <= 0) {
					continue;
				}
				int result = memArray[i][j-N] + memArray[i][N];
				// printf("AccessedN: [%d][%d]%d, [%d][%d]%d\n", i, j-N, memArray[i][j-N], i, N, memArray[i][N]);
				if (N == 1 || result < divL) {
					divL = result;
				}
			}
			if (divW != -1 && divL != -1) {
				// None of them is -1
				int minDivide = divW < divL ? divW : divL;
				min = minDivide < direct ? minDivide : direct;
			}
			else if (divW != -1) {
				// divL = -1
				int minDivide = divW;
				min = minDivide < direct ? minDivide : direct;
			}
			else if (divL != -1) {
				// divW = -1
				int minDivide = divL;
				min = minDivide < direct ? minDivide : direct;
			}
			else {
				// Both of them are -1
				min = direct;
			}
			// printf("Set i:%d j:%d as %d\n", i, j, min);
			memArray[i][j] = min;
		}
	}

	int result = memArray[W][L];

	for (int i = 0; i < W+1; i++) {
		delete[] memArray[i];
	}
	delete[] memArray;
	return result;
}
