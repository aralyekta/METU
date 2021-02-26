#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <functional>
#include <cstddef>
#include <ostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>

#include <iostream>   // you may use it for debugging your code


class DefaultBalanceCondition    // default BST, do not change
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      return true;
    }
};


template <typename Key, typename Object,
          typename BalanceCondition=DefaultBalanceCondition,
	  typename Comparator=std::less<Key> >
class BinarySearchTree
{
  public:  /* DO NOT CHANGE */
    struct Node   // core structure of BinarySearchTree
    {
       Key key;         // unique key
       Object data;     // data to be stored, characterized by key
       Node * left;     // pointer to left subtree
       Node * right;    // pointer to right subtree
       size_t height;   // height of the node
       size_t subsize;  // size of the subtree node roots including itself

       Node(const Key &, const Object &, 
            Node *, Node *, size_t =0, size_t =1);   // Node constructor
    };

  public:  /* DO NOT CHANGE PROTOTYPES */
    BinarySearchTree();  // zero-parameter constructor
    BinarySearchTree(const std::list<std::pair<Key, Object> > &); // list is always sorted!
    ~BinarySearchTree();  // destructor

  public:  /* DO NOT CHANGE PROTOTYPES */
    void insert(const Key &, const Object &);  // insert new Key-Object
    void remove(const Key &);  // remove Node characterized by Key
    void toCompleteBST();  // convert into a complete BST

  public:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &) const; // single item
    std::list<Node *> find(const Key &, const Key &) const; // range queries
    int height() const;  // return the height of the tree
    size_t size() const; // return the number of items in the tree
    bool empty() const;  //return whether the tree is empty or not
    Node * getRoot() const; // return a pointer to the root of the tree
    void print(std::ostream &) const;  // print tree structure into an output stream


  private:  /* DO NOT CHANGE DATA TYPES AND IDENTIFIERS */
    Node * root;                     // designated root
    size_t numNodes;                 // size
    Comparator isLessThan;           // operator upon which BST nodes are arranged
    BalanceCondition isBalanced;     // signals whether the signal is balanced
  
  private:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &, Node *) const;
    int height(Node *) const;
    int subsize(Node *) const;
    void print(Node *, std::ostream &) const;

    // Define your const private utility functions below this line

  private:
    void makeEmpty(Node * &);       // utility for destructor
    
    // Define your private utility functions below this line
    Node *generateTree(int);
    void setValues(Node *, typename std::list<std::pair<Key, Object> >::const_iterator &);
    void treeToList(Node *, Node **, int);
    Node * setPtrFromArray(Node **, int, int);
    void recursiveSearch(Node *, std::list<Node *> &, const Key &, const Key &) const;
    Node *insertRec(Node *, const Key &, const Object &);
    void updateHeightAndSubSize(Node *);
    Node *completeSubTree(Node *);
    Node *removeRec(Node *, const Key &);
    Node *findInOrderNext(Node *);
    int Left_n_ExceptRoot(int);

  private: /* DO NOT CHANGE PROTOTYPES: compiler defaults are blocked */  
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    // Define more below this line if needed

};

#endif

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::completeSubTree(typename BinarySearchTree<K,O,B,C>::Node *node)
{
  if (node)
  {
    size_t n = node->subsize;
    Node ** array = new Node *[n];
    Node * root_return;
    treeToList(node, array, -1);
    /*
    for (int i = 0; i < n; i++)
    {
      std::cout << (*(array[i])).data << " ";
    }
    std::cout << "\n";
    */
    root_return = setPtrFromArray(array, 0, n-1);
    delete[] array;
    return root_return;
  }
  else
  {
    return NULL;
  }
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::updateHeightAndSubSize(typename BinarySearchTree<K,O,B,C>::Node *node)
{
  Node *left_child, *right_child;
  if (node)
  {
    left_child = node->left;
    right_child = node->right;
    if(left_child && right_child)
    {
      node->height = left_child->height > right_child->height ? left_child->height + 1: right_child->height + 1;
      node->subsize = left_child->subsize + right_child->subsize + 1;
    }
    else if (left_child)
    {
      node->height = left_child->height + 1;
      node->subsize = left_child->subsize + 1;
    }
    else if (right_child)
    {
      node->height = right_child->height + 1;
      node->subsize = right_child->subsize + 1;
    }
    else
    {
      node->height = 0;
      node->subsize = 1;
    }
  }
}

// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::Node::
Node(const K & _k, const O & _d, Node * _l, Node * _r, size_t _h, size_t _s)
  : key(_k), data(_d), left(_l), right(_r), height(_h), subsize(_s)
{
}

// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree()
  : root(NULL), numNodes(0)  //comparator(C() ??)
{
}

template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::Left_n_ExceptRoot(int n)
{
  int ideal_height, parent_nodes, n_except_leaves, max_leaves, current_leaves, left_n;
  if (n <= 1)
  {
    return 0;
  }
  else
  {
    ideal_height = log2(n);
    parent_nodes = pow(2, ideal_height - 1);
    n_except_leaves = pow(2, ideal_height) - 1;
    max_leaves = 2 * parent_nodes;
    current_leaves = n - n_except_leaves;
    left_n = (n_except_leaves - 1) / 2;
    if (current_leaves >= (max_leaves / 2))
    {
      left_n += max_leaves / 2;
    }
    else
    {
      left_n += current_leaves;
    }
    return left_n;
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node * 
BinarySearchTree<K,O,B,C>::generateTree(int n)
{
  int left_n = 0, right_n = 0;
  int height_left = -1, height_right = -1;
  if (n > 0)
  {
    Node *node = new Node(K(), O(), NULL, NULL);
    left_n = Left_n_ExceptRoot(n);
    right_n = n - left_n - 1;
    node->subsize = n;
    if (left_n > 0)
    {
      node->left = generateTree(left_n);
      height_left = node->left->height;
    }
    else
    {
      node->left = NULL;
    }
    if (right_n > 0)
    {
      node->right = generateTree(right_n);
      height_right = node->right->height;
    }
    else
    {
      node->right = NULL;
    }
    node->height = height_left > height_right ? height_left+1 : height_right+1;
    return node;
  }
  else
  {
    return NULL;
  }
}

template <typename K, typename O, typename B, typename C>
void 
BinarySearchTree<K,O,B,C>::setValues(typename BinarySearchTree<K,O,B,C>::Node *node, typename std::list<std::pair<K,O> >::const_iterator &itr)
{
  if (node)
  {
    setValues(node->left, itr);
    node->key = itr->first;
    node->data = itr->second;
    itr++;
    setValues(node->right, itr);
  }
}

// IMPLEMENT
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree(const std::list<std::pair<K,O> > & datalist)
   : root(NULL), numNodes(0)  // change it as you'd like
{
  typename std::list<std::pair<K,O>>::const_iterator itr = datalist.begin();
  int leng = datalist.size();
  numNodes += leng;
  root = generateTree(leng);
  setValues(root, itr);
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::treeToList(BinarySearchTree<K,O,B,C>::Node *node, BinarySearchTree<K,O,B,C>::Node ** array, int prev_index)
{
  int left_n = 0, root_index;
  if (node)
  {
    if (node->left)
    {
      left_n = node->left->subsize;
    }
    root_index = left_n + prev_index + 1;
    array[root_index] = node;
    treeToList(node->left, array, prev_index);
    treeToList(node->right, array, root_index);
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::setPtrFromArray(BinarySearchTree<K,O,B,C>::Node ** array, int start_index, int end_index)
{
  //std::cout << "Start: " << start_index << " and end: " << end_index << "\n";
  Node *left_root, *right_root, *center_root;
  int left_n, n, center_index;
  if (start_index < end_index)
  {
    n = end_index - start_index + 1;
    left_n = Left_n_ExceptRoot(n);
    center_index = start_index + left_n;
    left_root = setPtrFromArray(array, start_index, center_index-1);
    right_root = setPtrFromArray(array, center_index+1, end_index);
    center_root = array[center_index];    
    center_root->left = left_root;
    center_root->right = right_root;
    updateHeightAndSubSize(center_root);
    return center_root;
  }
  else if (start_index == end_index)
  {
    center_root = array[start_index];
    center_root->left = NULL;
    center_root->right = NULL;
    updateHeightAndSubSize(center_root);
    return center_root;
  }
  else
  {
    return NULL;
  }
}

// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::toCompleteBST()
{
  if (this->root)
  {
    this->root = completeSubTree(this->root);
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::insertRec(typename BinarySearchTree<K,O,B,C>::Node *node, const K& key, const O& object)
{
  int ideal_height, current_height;
  if (node)
  {
    if (isLessThan(key, node->key))
    {
      if (node->left)
      {
        node->left = insertRec(node->left, key, object);
        updateHeightAndSubSize(node);
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          node = completeSubTree(node);
        }
        return node;
      }
      else
      {
        node->left = new Node(key, object, NULL, NULL);
        updateHeightAndSubSize(node->left);
        updateHeightAndSubSize(node);
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          node = completeSubTree(node);
        }
        return node;
      }
    }
    else if (isLessThan(node->key, key))
    {
      if (node->right)
      {
        node->right = insertRec(node->right, key, object);
        updateHeightAndSubSize(node);
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          node = completeSubTree(node);
        }
        return node;
      }
      else
      {
        node->right = new Node(key, object, NULL, NULL);
        updateHeightAndSubSize(node->right);
        updateHeightAndSubSize(node);
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          node = completeSubTree(node);
        }
        return node;
      }
    }
    else
    {
      node->data = object;
      return node;
    }
  }
  else
  {
    node = new Node(key, object, NULL, NULL);
    updateHeightAndSubSize(node);
    return node;
  }
}

// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{
  if (this->root)
  {
    this->root = insertRec(this->root, k, x);
    numNodes++;
  }
  else
  {
    this->root = new Node(k, x, NULL, NULL);
    numNodes++;
    updateHeightAndSubSize(this->root);
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::findInOrderNext(typename BinarySearchTree<K,O,B,C>::Node *node)
{
  typename BinarySearchTree<K,O,B,C>::Node *returnNodePtr;
  if (node)
  {
    if (node->left)
    {
      returnNodePtr = findInOrderNext(node->left);
      if (returnNodePtr == node->left)
      {
        node->left = returnNodePtr->right;
      }
      updateHeightAndSubSize(node);
      return returnNodePtr;
    }
    else
    {
      return node;
    }
  }
  else
  {
    return NULL;
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::removeRec(typename BinarySearchTree<K,O,B,C>::Node *node, const K& key)
{
  int ideal_height, current_height;
  typename BinarySearchTree<K,O,B,C>::Node *handle, *inOrderNext;
  if (node)
  {
    K root_key = node->key;
    size_t prevSubsize = 0, prevNode = 0, currNode = 0;
    if (isLessThan(key, root_key))
    {
      //std::cout << "Sola incem\n";
      if (node->left)
      {
        //std::cout << "ife girdim\n";
        prevSubsize = node->left->subsize;
        //std::cout << "ifteyim\n";
        prevNode = 1;
      }
      //std::cout << "Recursive çağırıyom\n";
      node->left = removeRec(node->left, key);
      if (node->left)
      {
        currNode = 1;
      }
      if ((prevNode != currNode) || (node->left && prevSubsize != node->left->subsize))
      {
        updateHeightAndSubSize(node);
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          //std::cout << "Key : " << node->key << " is inbalanced\n";
          node = completeSubTree(node);
        }
      }
      return node;
    }
    else if (isLessThan(root_key, key))
    {
      //std::cout << "Sağa incem\n";
      if (node->right)
      {
        prevSubsize = node->right->subsize;
        prevNode = 1;
      }
      node->right = removeRec(node->right, key);
      if (node->right)
      {
        currNode = 1;
      }
      if ((prevNode != currNode) || (node->right && prevSubsize != node->right->subsize))
      {
        updateHeightAndSubSize(node);
        //std::cout << "Key is: " << node->key << " height: " << node->height << " subsize: " << node->subsize << "\n";
        ideal_height = log2(node->subsize);
        current_height = node->height;
        if (node->subsize > 1 && !isBalanced(current_height, ideal_height))
        {
          //std::cout << "Key : " << node->key << " is inbalanced\n";
          node = completeSubTree(node);
        }
      }
      return node;
    }
    else
    {
      if (!node->left && !node->right) //leaf
      {
        //std::cout << "Silcem, leaf\n";
        delete node;
        return NULL;
      }
      else if (!node->left) //right child
      {
        //std::cout << "Silcem, sadece sağ child var\n";
        handle = node->right;
        delete node;
        return handle;
      }
      else if (!node->right) //left child
      {
        //std::cout << "Silcem, sadece left child var\n";
        handle = node->left;
        delete node;
        return handle;
      }
      else //both children
      { 
        //std::cout << "Silcem, both children var\n";
        inOrderNext = findInOrderNext(node->right);
        handle = node;
        if (inOrderNext == node->right)
        {
          inOrderNext->left = node->left;
        }
        else
        {
          inOrderNext->left = node->left;
          inOrderNext->right = node->right;
        }
        delete handle;
        updateHeightAndSubSize(inOrderNext);
        //std::cout << "Inorder successor is: " << inOrderNext->key << " height: " << inOrderNext->height << " subsize: " << inOrderNext->subsize << "\n";
        ideal_height = log2(inOrderNext->subsize);
        current_height = inOrderNext->height;
        if (!isBalanced(current_height, ideal_height))
        {
          //std::cout << "Not balanced, key: " << inOrderNext->key << "\n";
          inOrderNext = completeSubTree(inOrderNext);
        }
        return inOrderNext;
      }
    }
  }
  else
  {
    return node;
  }
}

// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{
  size_t prev_subsize, cur_subsize;
  if (this->root)
  {
    prev_subsize = this->root->subsize;
    this->root = removeRec(this->root, k);
    cur_subsize = this->root->subsize;
    //std::cout << "prev subsize: " << prev_subsize << " cur subsize: " << cur_subsize << " and numNodes: " << numNodes << "\n";
    if (prev_subsize != cur_subsize)
    {
      numNodes--;
    }
  }
}



// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key) const
{
  return find(key, root);
}



// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key, Node * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::recursiveSearch(BinarySearchTree<K,O,B,C>::Node *node, std::list<Node *> &ranges, const K &lower, const K &upper) const
{
  if (node)
  {
    K root_key = node->key;
    if (isLessThan(lower, root_key) && !isLessThan(root_key, upper)) // = included in upper
    {
      recursiveSearch(node->left, ranges, lower, upper);
      if (!isLessThan(upper, root_key) && !isLessThan(root_key, lower)) // = included in both
      {
        ranges.push_back(node);
      }
    }
    else if (!isLessThan(lower, root_key) && isLessThan(root_key, upper)) // = included in lower
    {
      if (!isLessThan(upper, root_key) && !isLessThan(root_key, lower)) // = included in both
      {
        ranges.push_back(node);
      }
      recursiveSearch(node->right, ranges, lower, upper);
    }
    else
    {
      recursiveSearch(node->left, ranges, lower, upper);
      if (!isLessThan(upper, root_key) && !isLessThan(root_key, lower)) // = included in both
      {
        ranges.push_back(node);
      }
      recursiveSearch(node->right, ranges, lower, upper);
    }
  }
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
std::list<typename BinarySearchTree<K,O,B,C>::Node *>
BinarySearchTree<K,O,B,C>::find(const K & lower, const K & upper) const
{
  std::list<Node *> ranges;
  recursiveSearch(this->root, ranges, lower, upper);
  return ranges;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::getRoot() const
{
  return root;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height() const
{
  return height(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height(Node * t) const
{
  return (t == NULL) ? -1 : t->height;
}


// private utility
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::subsize(Node * t) const
{
  return (t == NULL) ? 0 : t->subsize;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
size_t
BinarySearchTree<K,O,B,C>::size() const
{
  return numNodes;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
bool
BinarySearchTree<K,O,B,C>::empty() const
{
  return numNodes == 0;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::makeEmpty(Node * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;

    --numNodes;
  }
  
  t = NULL;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::~BinarySearchTree()
{
  makeEmpty(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(Node * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << ",S" << t->subsize << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}


// do not change
template <typename K, typename O, typename B, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,B,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}