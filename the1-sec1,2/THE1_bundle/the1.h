#ifndef THE1_H
#define THE1_H

#define MAX_LENGTH 1000
#define MAX(a, b) (a<b) ? (b) : (a)
#define MIN(a, b) (a>b) ? (b) : (a)
#define MAX_VAL 999999
#define MIN_VAL 0

void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user);

void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value);

void delete_node_rec(int binary_tree[MAX_LENGTH], int node);

void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth);

int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root);

int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root);

int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value);

int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value);

void print_binary_tree_values(int binary_tree[MAX_LENGTH]);

#endif
