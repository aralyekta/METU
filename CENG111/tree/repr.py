from tree_functions import *

node_left = makenode(56)
node_left = [7, node_left, []]

node_right = makenode(65)
node_right = [8, node_right,[]]

node_right = [21,node_left,node_right]
node_right_last = [20,[],node_right]

node_left = makenode(4)
node_right = makenode(5)

node_left = [11,node_left,node_right]
node = makenode(6)
node_right = [12,node,[]]

node_left_last = [10,node_left,node_right]

tree = [1,node_left_last,node_right_last]

print tree
