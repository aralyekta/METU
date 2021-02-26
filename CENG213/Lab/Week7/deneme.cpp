#include "ThreeHeapPriorityQueue.h"
#include "UnderflowException.h"
#include "IllegalArgumentException.h"


int main()
{
  
  ThreeHeapPriorityQueue<int> deneme;
  cout << deneme.isEmpty() << "\n";
  deneme.add(55);
  
  deneme.add(-12);
  deneme.print();
  deneme.add(86);
  deneme.print();
  deneme.add(47);
  deneme.print();
  deneme.add(91);
  deneme.print();
  deneme.add(62);
  deneme.print();
  deneme.add(29);
  deneme.print();
  deneme.add(3);
  deneme.print();
  
  return 0;
}
