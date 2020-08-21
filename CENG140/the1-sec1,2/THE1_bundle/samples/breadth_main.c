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
	
	printf("Breadth first search results:\n");

    printf("%d is at %d in tree with root number %d.\n", 8, breadth_first_search_itr(binary_tree, 0,8), 0);
    printf("%d is at %d in tree with root number %d.\n", 8, breadth_first_search_itr(binary_tree, 1,8), 1);
    printf("%d is at %d in tree with root number %d.\n", 7, breadth_first_search_itr(binary_tree, 0,7), 0);
    printf("%d is at %d in tree with root number %d.\n", 1, breadth_first_search_itr(binary_tree, 6,1), 6);
    printf("%d is at %d in tree with root number %d.\n", 2, breadth_first_search_itr(binary_tree, 14,2), 14);
    printf("%d is at %d in tree with root number %d.\n", 35, breadth_first_search_itr(binary_tree, 0,35), 0);
    printf("%d is at %d in tree with root number %d.\n", 4, breadth_first_search_itr(binary_tree, 2,4), 2);
 	
	return 0;
}
