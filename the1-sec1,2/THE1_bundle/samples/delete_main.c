#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	initialize_the_tree(binary_tree, 0);
	
    binary_tree[0] = 15;
    binary_tree[1] = 4;
    binary_tree[2] = 8;
    binary_tree[3] = 1;
    binary_tree[4] = 8;
    binary_tree[5] = 3;
    binary_tree[6] = 7;
    binary_tree[10] = 1;
    binary_tree[12] = 2;
    binary_tree[13] = 2;
    binary_tree[14] = 4;
    binary_tree[26] = 1;
    binary_tree[28] = 1;
    binary_tree[29] = 1;
    binary_tree[30] = 2;
    binary_tree[62] = 1;
    
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);
	
    delete_node_rec(binary_tree, 2);
    
    printf("Values after node 2 is deleted\n");
	print_binary_tree_values(binary_tree);
	
	return 0;
}
