#include <iostream>
#include <random>
#include <ctime>
#include "the5.h"

int getRandomInt(int max){
        int r = rand() % max + 1;
        return r;
}

void createAndWritePartitions(int numberOfPartitions, bool** partitions, int W, int L){

	std::cout << "Field: " << W << " x " << L << std::endl;	

	for(int p = 0; p < numberOfPartitions; p++){
		int w = getRandomInt(W);
		int l = getRandomInt(L);
		while (partitions[w][l]){		// make sure that no two partitions are same
			w = getRandomInt(W);
			l = getRandomInt(L);
		}
		partitions[w][l] = true;
		std::cout << "Partition " << (p+1) << ": " << w << " x " << l << std::endl;
	}
}

void testRecursive(int W, int L, bool** partitions){
	std::cout << "\n***Testing Recursive Method***\n"; 
	clock_t begin, end;
	double duration;
	int numberOfCalls = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	int wastage = recursiveMethod(W, L, partitions, &numberOfCalls);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Calls: " << numberOfCalls << std::endl;
	std::cout << "******************************\n";
}

void testMemoization(int W, int L, bool** partitions){
	std::cout << "\n***Testing Memoization Method***\n";
	clock_t begin, end;
	double duration;
	int numberOfCalls = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;
	
	int wastage = memoizationMethod(W, L, partitions, &numberOfCalls);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Calls: " << numberOfCalls << std::endl;
	std::cout << "******************************\n";
}

void testBottomUp(int W, int L, bool** partitions){
	std::cout << "\n***Testing Bottom-up Method***\n";
	clock_t begin, end;
	double duration;
	int numberOfIterations = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;
	
	int wastage = bottomUpMethod(W, L, partitions, &numberOfIterations);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Iterations: " << numberOfIterations << std::endl;
	std::cout << "******************************\n";
}

void test(){

	while (true) {
		// Field
		int W = 600;
		int L = 600;

		// Initialization for partitions
		bool** partitions = new bool*[W+1];
		for(int i = 0; i < W+1; i++){
			partitions[i] = new bool[L+1];
			for (int j = 0; j < L+1; j++){
				partitions[i][j] = false;
			}
		}

		int numberOfPartitions = 25;
		printf("Will create partitions\n");
		createAndWritePartitions(numberOfPartitions, partitions, W, L);
		printf("Created partitions\n");

		int num1 = 0;
		int num2 = 0;
		int num3 = 0;

		// testRecursive(W, L, partitions);
		// testMemoization(W, L, partitions);
		// testBottomUp(W, L, partitions);

		// int res1 = recursiveMethod(W, L, partitions, &num1);
		int res2 = memoizationMethod(W, L, partitions, &num2);
		int res3 = bottomUpMethod(W, L, partitions, &num3);
		if (res2 != res3) {
			printf("WRONG\n");
			break;
		}
		else {
			printf("CORRECT: %d\n", res2);
			break;
		}
	}

}

int main(){
	srandom(time(0));
    test();

	// int W = 5;
	// int L = 3;

	// bool** partitions = new bool*[W+1];
	// for(int i = 0; i < W+1; i++){
	// 	partitions[i] = new bool[L+1];
	// 	for (int j = 0; j < L+1; j++){
	// 		partitions[i][j] = false;
	// 	}
	// }

	// int numberOfPartitions = 2;
	// int x = 0;
	// int y = 0;
	// int z = 0;
	// int *numOfCalls1 = &x;
	// int *numOfCalls2 = &y;
	// int *numOfCalls3 = &z;
	// recursiveMethod(W, L, partitions, numOfCalls1);
	// memoizationMethod(W, L, partitions, numOfCalls2);
	// int result = bottomUpMethod(W, L, partitions, numOfCalls3);

	// printf("%d\n", result);

	// for (int i = 0; i < W+1; i++) {
	// 	delete[] partitions[i];
	// }
	// delete[] partitions;

    return 0;
}
