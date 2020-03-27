#include <stdio.h>
#include <math.h>
#include "the1.h"

void print_n_times(int, char);
int isleaf(int[], int);

void print_n_times(int n, char c)
{
	if (n > 0)
	{
		printf("%c",c);
		print_n_times(n-1,c);
	}
}

int isleaf(int binary_tree[MAX_LENGTH],int node)
{
	if (binary_tree[2*node+1] == -1 && binary_tree[2*node+2] == -1)
		return 1;
	else
		return 0;
}

void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) 
{
	int i, num_input, index, val;
	for (i = 0 ; i < MAX_LENGTH ; i++)
	{
		binary_tree[i] = -1;
	}
	if (get_values_from_user != 0)
	{
		scanf("%d", &num_input);
		for (i = 0 ; i < num_input ; i++)
		{
			scanf("%d %d", &index, &val);
			if (index <= MAX_LENGTH && val <= MAX_VAL && val >= MIN_VAL && binary_tree[index] == -1)
			{
				binary_tree[index] = val;
			}

		}
	}
}

void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) 
{
	if (where == 'l' && binary_tree[2*node+1] == -1)
	{
		binary_tree[(2*node)+1] = value;
	}
	else if (where == 'r' && binary_tree[2*node+2] == -1)
	{
		binary_tree[(2*node)+2] = value;
	}
	else if (where == 'i' && binary_tree[node] == -1)
	{
		binary_tree[node] = value;
	}
}

void delete_node_rec(int binary_tree[MAX_LENGTH], int node) 
{
	if (binary_tree[node] != -1)
	{
		binary_tree[node] = -1;
		delete_node_rec(binary_tree,2*node+1);
		delete_node_rec(binary_tree,2*node+2);
	}
}

void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) 
{
	if (binary_tree[root] != -1 && depth >= 0)
	{
		draw_binary_tree_rec(binary_tree,2*root+1,depth-1);
		print_n_times(depth,'\t');
		printf("%d\n",binary_tree[root]);
		draw_binary_tree_rec(binary_tree,2*root+2,depth-1);
	}
}

int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) 
{
	int left_child = 0, right_child = 0, height_max = 0;
	if (isleaf(binary_tree, root))
	{
		return 0;
	}
	left_child = find_height_of_tree_rec(binary_tree, 2*root+1);
	right_child = find_height_of_tree_rec(binary_tree, 2*root+2);
	height_max = MAX(left_child, right_child);
	return ++height_max;
}

int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) 
{
	int left_val, right_val, own_val, min_of_two;
	if (binary_tree[root] != -1)
	{
		if (isleaf(binary_tree,root))
		{
			return binary_tree[root];
		}
		left_val = (find_min_of_tree_rec(binary_tree,2*root+1));
		right_val = (find_min_of_tree_rec(binary_tree,2*root+2));
		own_val = binary_tree[root];
		min_of_two = MIN(left_val, right_val);
		return MIN(min_of_two, own_val);
	}
	return MAX_VAL;
}

int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value)
{
	int queue[MAX_LENGTH];
	int i, length = 0, index_to_append = 1;
	for ( i = root ; i < MAX_LENGTH; i++)
	{
		if (binary_tree[i] != -1)
			length++;
	}
	queue[0] = root;
	if (binary_tree[root] == value)
		return root;
	for (i = 0 ; i < length-1 ; i++)
	{
		if (i == index_to_append)
		{
			return -1;
		}
		root = queue[i];
		if (binary_tree[2*root+1] != -1)
		{
			if (binary_tree[2*root+1] == value)
				return 2*root+1;
			queue[index_to_append] = 2*root+1;
			index_to_append++;
		}
		if (binary_tree[2*root+2] != -1)
		{
			if (binary_tree[2*root+2] == value)
				return 2*root+2;
			queue[index_to_append] = 2*root+2;
			index_to_append++;
		}
	}
	return -1;
}

int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) 
{
	int left_order, right_order;
	if (isleaf(binary_tree, root))
	{
		if (binary_tree[root] == value)
		{
			return root;
		}
		else
			return -1;
	}
	left_order = depth_first_search_rec(binary_tree, 2*root+1, value);
	if (left_order != -1)
	{
		return left_order;
	}
	else 
	{
		if (binary_tree[root] == value)
		{
			return root;
		}
		else 
		{
			right_order = depth_first_search_rec(binary_tree, 2*root+2, value);
			if (right_order != -1)
			{
				return right_order;
			}
			else 
			{
				return -1;
			}
		}
	}
}

void print_binary_tree_values(int binary_tree[MAX_LENGTH]) 
{
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }
}


