#include "Deque.h"

int main() {
   Deque dq;

   dq.inject(5);
   dq.inject(10);
   
   cout << "get rear element: " << dq.getBack() << endl;
   cout << "get front element: " <<  dq.getFront() << endl;

   dq.eject();

    cout << "After delete rear element new rear become: " << dq.getBack() << endl;

   dq.push(15);

   cout << "inserting element at front end: 15" << endl;

   cout << "get front element: " <<  dq.getFront() << endl;

   dq.pop();

   cout << "After delete front element new front become: " << dq.getFront() << endl;

   /*
    for (int i=1; i<11; i++) {
       dq.inject(i);
    }
   
    cout << "get rear element: " << dq.getBack() << endl; //10
    
    dq.eject();
    cout << "After delete rear element new rear become: " << dq.getBack() << endl; //9
    
    dq.eject();
    cout << "After delete rear element new rear become: " << dq.getBack() << endl; //8
    
    
    cout << "Insert element at rear end: 12" << endl;
    dq.inject(12);
    
    cout << "insert element at rear end: 11" << endl;
    dq.inject(11);
    
    cout << "get rear element: " << dq.getBack() << endl; //11
    
    dq.eject();
    cout << "After delete rear element new rear become: " << dq.getBack() << endl; //12
    
    cout << "inserting element at front end: 15" << endl;
    dq.push(15);
    
    cout << "get front element: " <<  dq.getFront() << endl; //15

    
    cout << "After delete front element new front become: " << dq.getFront() << endl; //1
    */
    return 0;
}