#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	int get_values_from_user;
	scanf("%d", &get_values_from_user);
	initialize_the_tree(binary_tree, get_values_from_user);

	print_binary_tree_values(binary_tree);

	return 0;
}
