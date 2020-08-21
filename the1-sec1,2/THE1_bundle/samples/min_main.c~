#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	initialize_the_tree(binary_tree, 0);
	
    binary_tree[0] = 15;
    binary_tree[1] = 4;
    binary_tree[2] = 8;
    binary_tree[3] = 12;
    binary_tree[4] = 8;
    binary_tree[5] = 3;
    binary_tree[6] = 7;
    binary_tree[10] = 6;
    binary_tree[12] = 2;
    binary_tree[13] = 2;
    binary_tree[14] = 7;
    binary_tree[26] = 3;
    binary_tree[28] = 3;
    binary_tree[29] = 6;
    binary_tree[30] = 9;
    binary_tree[62] = 5;
    
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);
	
    printf("Min value of tree with root[%d] is %d\n", 0, find_min_of_tree_rec(binary_tree, 0));
    printf("Min value of tree with root[%d] is %d\n", 1, find_min_of_tree_rec(binary_tree, 1));
    printf("Min value of tree with root[%d] is %d\n", 2, find_min_of_tree_rec(binary_tree, 2));
    printf("Min value of tree with root[%d] is %d\n", 14, find_min_of_tree_rec(binary_tree, 14));
    	
	return 0;
}
