#include "bst.h"
#include <iostream>
/*
void showlist(std::list<BinarySearchTree<int, float>::Node *> list)
{
  std::list<int, float>::iterator it;
  for (it = list.begin(); it!=list.end(); ++it)
  {
    std::cout << "\t" << *it;
  }
  std::cout << "\n";
}
*/

class BalanceCondition
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      if (current_height > 2 * ideal_height)
        return false;
      return true;
    }
};

class DelicateBalance
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      return false;
    }
};


class AdditionalBalance
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      if (current_height > ideal_height)
      {
         return false;
      }
      return true;
    }
};

int main()
{
  BinarySearchTree<int, float> empty_bst;

  empty_bst.print(std::cout);

  std::list<std::pair<int, float> > datalist;
  //for (int j = 0; j < 100; j++)
  //{
    /*
    for (int i = 0; i < 12; ++i)
    {
      datalist.push_back(std::make_pair(i, i));
    }
    */
    
    
    /*
    datalist.push_back(std::make_pair(0, 0));
    datalist.push_back(std::make_pair(1, 1));
    datalist.push_back(std::make_pair(2, 2));
    datalist.push_back(std::make_pair(3, 3));
    datalist.push_back(std::make_pair(4, 4));
    datalist.push_back(std::make_pair(7, 7));
    datalist.push_back(std::make_pair(8, 8));
    datalist.push_back(std::make_pair(10, 10));
    */

    std::list<std::pair<int, float> >::const_iterator itr = datalist.begin();

    std::cout << "Populating sorted data list contains these key-object values:" << std::endl;
    for ( ; itr != datalist.end(); ++itr)
    {
      std::cout << itr->first << " " << itr->second << std::endl;
    }
    std::cout << std::endl;

    BinarySearchTree<int, float, AdditionalBalance> list_bst(datalist);
    
    
    list_bst.insert(4, 4);
    list_bst.insert(2, 2);
    list_bst.insert(8, 8);
    list_bst.insert(1, 1);
    list_bst.insert(3, 3);
    list_bst.insert(6, 6);
    list_bst.insert(10, 10);
    list_bst.insert(0, 0);
    list_bst.insert(5, 5);
    list_bst.insert(7, 7);
    list_bst.insert(9, 9);
    list_bst.insert(11, 11);
    


    /*
    for (int i = 0; i < 5; i++)
    {
      list_bst.insert(i+5, i+5);
    }
    */

    std::cout << "Constructed tree is as follows for AdditionalBalance condition: " << std::endl;
    
    //std::list<BinarySearchTree<int, float>::Node *>::iterator itro;
    //itro = list_bst.find(5,10).begin();
    //std::cout << ((list_bst.find(4,11)).size()) << "\n";
    //list_bst.toCompleteBST();
    list_bst.print(std::cout);
    std::cout << "\n";
    
    list_bst.remove(9);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(6);
    list_bst.print(std::cout);
    std::cout << "\n";
    
    list_bst.remove(2);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.toCompleteBST();
    list_bst.remove(20);
    list_bst.print(std::cout);
    std::cout << "\n";
    /*
    list_bst.remove(3);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(11);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(0);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(1);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(10);
    list_bst.print(std::cout);
    std::cout << "\n";
    list_bst.remove(4);
    list_bst.print(std::cout);
    std::cout << "\n";
    */
    //list_bst.remove(10);
    /*
    list_bst.print(std::cout);
    std::cout << "\n";
    
    list_bst.remove(18);
    list_bst.print(std::cout);
    std::cout << "\n";
    */
    //std::cout << list_bst.getRoot()->data << "\n";
  //}

  return 0;
}