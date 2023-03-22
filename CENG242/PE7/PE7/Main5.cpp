#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main()
{
    NodeManager* nm1 = new NodeManager();
    /*
    nm1->addRelation(50, 10);
    nm1->addRelation(10, 48);
    nm1->addRelation(48, 14);
    nm1->addRelation(50, 20);
    nm1->addRelation(20, 4);
    nm1->addRelation(20, 5);
    nm1->addRelation(20, 6);
    nm1->setDataToNode(50, '*');
    nm1->setDataToNode(6, '*');
    */
   
    nm1->addRelation(50, 10);
    nm1->setDataToNode(48, '*');
    nm1->setDataToNode(50, '*');
    nm1->addRelation(10, 48);
    nm1->setDataToNode(14, '*');
    nm1->setDataToNode(10, '*');
    nm1->addRelation(48, 14);
    nm1->setDataToNode(5, '*');
    nm1->addRelation(50, 20);
    nm1->setDataToNode(20, '*');
    nm1->addRelation(20, 4);
    nm1->addRelation(20, 5);
    nm1->setDataToNode(6, '*');
    nm1->addRelation(20, 6);
    nm1->setDataToNode(4, '*');
    
    delete nm1;
    return 0;
}