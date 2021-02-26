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
    void insertNormal(const Key &, const Object &); //DELETE THIS

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
    int Left_n_ExceptRoot(int);
    void treeToList(Node *, Node **, int);
    Node * setPtrFromArray(Node **, int, int);
    void recursiveSearch(Node *, std::list<Node *> &, const Key &, const Key &) const;
    void insertNormalRec(Node *, const Key &, const Object &);

  private: /* DO NOT CHANGE PROTOTYPES: compiler defaults are blocked */  
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    // Define more below this line if needed

};

#endif

// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::Node::
Node(const K & _k, const O & _d, Node * _l, Node * _r, size_t _h, size_t _s)
  : key(_k), data(_d), left(_l), right(_r), height(_h), subsize(_s)
{
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insertNormal(const K &key, const O &object)
{
  if (this->root)
  {
    insertNormalRec(this->root, key, object);
  }
  else
  {
    root = new Node(key, object, NULL, NULL);
    root->height = 0;
    root->subsize = 1;
  }
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insertNormalRec(typename BinarySearchTree<K,O,B,C>::Node *root, const K &key, const O &object)
{
  if (root)
  {
    if (isLessThan(key, root->key))
    {
      if (root->left)
      {
        insertNormalRec(root->left, key, object);
        if (root->right)
        {
          root->height = root->left->height > root->right->height ? root->left->height + 1 : root->right->height + 1;
          root->subsize = root->left->subsize + root->right->subsize + 1;
        }
        else
        {
          root->height = root->left->height + 1;
          root->subsize = root->left->subsize + 1;
        }
      }
      else
      {
        root->left = new Node(key, object, NULL, NULL);
        root->left->subsize = 1;
        root->left->height = 0;
        if (root->right)
        {
          root->height = root->left->height > root->right->height ? root->left->height + 1 : root->right->height + 1;
          root->subsize = root->left->subsize + root->right->subsize + 1;
        }
        else
        {
          root->height = root->left->height + 1;
          root->subsize = root->left->subsize + 1;
        }
      }
    }
    else 
    {
      if (root->right)
      {
        insertNormalRec(root->right, key, object);
        if (root->left)
        {
          root->height = root->left->height > root->right->height ? root->left->height + 1 : root->right->height + 1;
          root->subsize = root->left->subsize + root->right->subsize + 1;
        }
        else
        {
          root->height = root->right->height + 1;
          root->subsize = root->right->subsize + 1;
        }
      }
      else
      {
        root->right = new Node(key, object, NULL, NULL);
        root->right->subsize = 1;
        root->right->height = 0;
        if (root->left)
        {
          root->height = root->left->height > root->right->height ? root->left->height + 1 : root->right->height + 1;
          root->subsize = root->left->subsize + root->right->subsize + 1;
          
        }
        else
        {
          root->height = root->right->height + 1;
          root->subsize = root->right->subsize + 1;
        }
      }
    }
  }
}

// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree()
  : root(NULL), numNodes(0)  //comparator(C() ??)
{
}

template <typename K, typename O, typename B, typename C>
int BinarySearchTree<K,O,B,C>::Left_n_ExceptRoot(int n)
{
  int average_n, sub_height = 0, n_except_leaf_half, max_leaf_half, left_n;
  if (n <= 0)
  {
    return 0;
  }
  else
  {
    average_n = n/2;
    if (average_n != 0)
    {
      if (2 * average_n != n)
      {
        sub_height = (int)log2((float)n/2+1);
        average_n++;
      }
      else
      {
        sub_height = (int)log2((float)n/2);
      }
    }
    n_except_leaf_half = pow(2, sub_height) - 1;
    max_leaf_half = pow(2, sub_height);
    if (n-2*n_except_leaf_half >= max_leaf_half)
    {
      left_n = n_except_leaf_half + max_leaf_half;
    }
    else
    {
      left_n = n - n_except_leaf_half;
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
    Node *root = new Node(K(), O(), NULL, NULL);
    n--;
    if (n > 0)
    {
      left_n = Left_n_ExceptRoot(n);
      right_n = n - left_n;
      root->subsize = left_n + right_n + 1;
      if (left_n > 0)
      {
        root->left = generateTree(left_n);
        height_left = root->left->height;
      }
      else
      {
        root->left = NULL;
      }
      if (right_n > 0)
      {
        root->right = generateTree(right_n);
        height_right = root->right->height;
      }
      else
      {
        root->right = NULL;
      }
      root->height = height_left > height_right ? height_left+1 : height_right+1;
      return root;
    }
    return root;
  }
  return NULL;
}


template <typename K, typename O, typename B, typename C>
void 
BinarySearchTree<K,O,B,C>::setValues(typename BinarySearchTree<K,O,B,C>::Node *root, typename std::list<std::pair<K,O> >::const_iterator &itr)
{
  if (root)
  {
    setValues(root->left, itr);
    root->key = itr->first;
    root->data = itr->second;
    itr++;
    setValues(root->right, itr);
  }
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree(const std::list<std::pair<K,O> > & datalist)
   : root(NULL), numNodes(0)  // change it as you'd like
{
  typename std::list<std::pair<K,O>>::const_iterator itr = datalist.begin();
  int leng = datalist.size();
  root = generateTree(leng);
  setValues(root, itr);
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::treeToList(BinarySearchTree<K,O,B,C>::Node * root, BinarySearchTree<K,O,B,C>::Node ** array, int prev_index)
{
  int left_n = 0, root_index;
  if (root)
  {
    if (root->left)
    {
      left_n = root->left->subsize;
    }
    root_index = left_n + prev_index + 1;
    array[root_index] = root;
    treeToList(root->left, array, prev_index);
    treeToList(root->right, array, root_index);
  }
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::setPtrFromArray(BinarySearchTree<K,O,B,C>::Node ** array, int start_index, int end_index)
{
  //Node *temp_left, *temp_right;
  Node *left_root, *right_root, *center_root;
  int left_n, n, center_index;
  if (start_index < end_index)
  {
    n = end_index - start_index + 1;
    n--; //Remove center_root
    left_n = Left_n_ExceptRoot(n);
    center_index = start_index + left_n;
    left_root = setPtrFromArray(array, start_index, center_index-1);
    right_root = setPtrFromArray(array, center_index+1, end_index);
    center_root = array[center_index];    
    center_root->left = left_root;
    center_root->right = right_root;
    if(left_root && right_root)
    {
      center_root->height = left_root->height > right_root->height ? left_root->height + 1: right_root->height + 1;
      center_root->subsize = left_root->subsize + right_root->subsize + 1;
    }
    else if (left_root)
    {
      center_root->height = left_root->height + 1;
      center_root->subsize = left_root->subsize + 1;
    }
    else if (right_root)
    {
      center_root->height = right_root->height + 1;
      center_root->subsize = right_root->subsize + 1;
    }
    else
    {
      center_root->height = 0;
      center_root->subsize = 1;
    }
    
    return center_root;
  }
  else if (start_index == end_index)
  {
    center_root = array[start_index];
    center_root->left = NULL;
    center_root->right = NULL;
    center_root->subsize = 1;
    center_root->height = 0;
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
  if ((*this).getRoot())
  {
    int n = this->getRoot()->subsize;
    Node ** array = new Node *[n];
    Node * root_return;
    treeToList(this->getRoot(), array, -1);
    
    /*
    for (int i = 0; i < n; i++)
    {
      std::cout << (*(array[i])).data << " ";
    }
    std::cout << "\n";
    */
    
    
    root_return = setPtrFromArray(array, 0, n-1);
    this->root = root_return;

    delete[] array;
  }
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{

}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{

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
BinarySearchTree<K,O,B,C>::recursiveSearch(BinarySearchTree<K,O,B,C>::Node *root, std::list<Node *> &ranges, const K &lower, const K &upper) const
{
  if (root)
  {
    int root_key = root->key;
    if (isLessThan(lower, root_key) && isLessThan(upper, root_key)) // = included in upper
    {
      recursiveSearch(root->left, ranges, lower, upper);
      if (isLessThan(root_key, upper) && isLessThan(lower, root_key)) // = included in both
      {
        ranges.push_back(root);
      }
    }
    else if (isLessThan(root_key, lower) && isLessThan(root_key, upper)) // = included in lower
    {
      if (isLessThan(root_key, upper) && isLessThan(lower, root_key)) // = included in both
      {
        ranges.push_back(root);
      }
      recursiveSearch(root->right, ranges, lower, upper);
    }
    else
    {
      recursiveSearch(root->left, ranges, lower, upper);
      if (isLessThan(root_key, upper) && isLessThan(lower, root_key)) // = included in both
      {
        ranges.push_back(root);
      }
      recursiveSearch(root->right, ranges, lower, upper);
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