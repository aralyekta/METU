#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	initialize_the_tree(binary_tree, 0);
	insert_node(binary_tree, 0, 'i', 15);
	
	insert_node(binary_tree, 0, 'l', 4);
	insert_node(binary_tree, 0, 'r', 8);
	
	insert_node(binary_tree, 1, 'l', 1);
	insert_node(binary_tree, 1, 'r', 8);


	insert_node(binary_tree, 4, 'r', 1);


	insert_node(binary_tree, 2, 'l', 3);
	insert_node(binary_tree, 2, 'r', 7);


	insert_node(binary_tree, 5, 'r', 2);


	insert_node(binary_tree, 6, 'l', 2);
	insert_node(binary_tree, 6, 'r', 4);


	insert_node(binary_tree, 12, 'r', 1);
	insert_node(binary_tree, 13, 'r', 1);


	insert_node(binary_tree, 14, 'l', 1);
	insert_node(binary_tree, 14, 'r', 2);

	insert_node(binary_tree, 30, 'r', 1);

	print_binary_tree_values(binary_tree);

	return 0;
}
