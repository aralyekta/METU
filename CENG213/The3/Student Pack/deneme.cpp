#include "HashTable.h"
#include <iostream>

int main()
{
  HashTable<int, int> deneme;
  //HashTable<int, int> deneme3;
  //deneme3 = deneme2;
  
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(5, 20);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(10, 30);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(15, 40);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(20, 40);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(25, 40);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(30, 40);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(35, 40);
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Insert(40, 20);
  
  //std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";  
  deneme.Insert(45, 30);  
  deneme.Insert(50, 40);
  deneme.Insert(55, 40);
  deneme.Insert(60, 40);
  deneme.Insert(65, 40);
  deneme.Insert(70, 40);
  std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  deneme.Delete(70);
  std::cout << deneme.Size() << " " << deneme.Capacity() << "\n";
  //deneme.Get(70);
  /*
  HashTable<int, int> deneme2(deneme);
  std::cout << deneme2.Size() << "\n";
  deneme2.Insert(5, 25);
  std::cout << deneme2.Size() << "\n";
  deneme3 = deneme;
  deneme3.Insert(10, 25);
  std::cout << deneme3.Size() << " " << deneme3.Capacity() << "\n";
  deneme3.Get(15);
  std::cout << deneme3.Size() << " " << deneme3.Capacity() << "\n";
  */
  return 0;
}