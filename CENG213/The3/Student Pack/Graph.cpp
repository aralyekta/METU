#include "Graph.h"

/*Do not add new libraries or files*/
#include <iostream> //DELET THIS

Graph::Graph() {
    // TODO: IMPLEMENT THIS FUNCTION.
}

Graph::Graph(const Graph& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    adjList = rhs.adjList;
}

Graph& Graph::operator=(const Graph& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    adjList = rhs.adjList;
    return *this;
}

Graph::~Graph() {
// TODO: IMPLEMENT THIS FUNCTION.
}


void Graph::addNode(const Node &node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    int countryId = node.getVid();
    list<Edge> emptyList;
    adjList.Insert(countryId, emptyList);
    nodeTable.Insert(countryId, node);
}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    // TODO: IMPLEMENT THIS FUNCTION.
    Edge edgeToAdd(tailNode, import);
    list<Edge> listToAdd = adjList.Get(headNode.getVid());
    list<Edge>::iterator itr = listToAdd.end();
    listToAdd.insert(itr, edgeToAdd);
    adjList.Insert(headNode.getVid(), listToAdd);
}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    list<Node> returnList;
    list<Edge> edgeList = adjList.Get(node.getVid());
    list<Edge>::iterator itr = edgeList.begin();
    for (; itr != edgeList.end(); itr++)
    {
        returnList.insert(returnList.end(), itr->getTailNode());
    }
    return returnList;
}

long Graph::getTotalImports(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    long totalImports = 0;
    list<Edge> edgeList = adjList.Get(node.getVid());
    list<Edge>::iterator itr = edgeList.begin();
    for (; itr != edgeList.end(); itr++)
    {
        totalImports += itr->getImport();
    }
    return totalImports;
}

void Graph::deleteNode(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    int adjListSize = adjList.Size();
    int *keys = new int[adjListSize];
    list<Edge> currentEdges;
    list<Edge> newEdges;
    list<Edge>::iterator itr, itr2;
    int i;
    adjList.getKeys(keys);
    for (i = 0; i < adjListSize; i++)
    {
        currentEdges = adjList.Get(keys[i]);
        newEdges.clear();
        for (itr = currentEdges.begin(),
        itr2 = newEdges.begin();
        itr != currentEdges.end(); itr = currentEdges.begin())
        {
            if (currentEdges.front().getTailNode().getVid() != node.getVid())
            {
                itr2 = newEdges.insert(itr2, currentEdges.front());
            }
            currentEdges.pop_front();
        }
        adjList.Insert(keys[i], newEdges);
    }
    adjList.Delete(node.getVid());
    nodeTable.Delete(node.getVid());
    delete[] keys;
}

pair<long, int> Graph::deleteMin(priority_queue<pair<long, int>> &pq, HashTable<int, bool> &visitedTable)
{
    pair<long, int> deletedNode;
    for (deletedNode = pq.top(), pq.pop(); visitedTable.Get(deletedNode.second) == true; deletedNode = pq.top(), pq.pop());
    return deletedNode;
}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    // TODO: IMPLEMENT THIS FUNCTION.
    HashTable<int, long> distTable;
    HashTable<int, int> pathTable;
    HashTable<int, bool> visitedTable;
    priority_queue<pair<long, int>> pq;
    int *validKeys = new int[nodeTable.Size()];
    int i, idOfMinVertex, idOfCurTailVertex;
    long alt, valueOfMinVertex;
    list<Edge> edgeListCurNode;
    list<Edge>::iterator itr;
    Node curNode;
    list<string> resultList;
    pair<long, int> deletedPair;
    nodeTable.getKeys(validKeys);
    if (validKeys != NULL)
    {
        for (i = 0; i < nodeTable.Size(); i++)
        {
            visitedTable.Insert(validKeys[i], false);
            pathTable.Insert(validKeys[i],validKeys[i]);
            if (validKeys[i] == srcNode.getVid())
            {
                pq.push(make_pair(0, validKeys[i]));
                distTable.Insert(validKeys[i], 0);
            }
            else
            {
                pq.push(make_pair(-1 * numeric_limits<int>::max(), validKeys[i]));
                distTable.Insert(validKeys[i], numeric_limits<int>::max());
            }
        }
        while (!pq.empty())
        {
            deletedPair = deleteMin(pq, visitedTable);
            idOfMinVertex = deletedPair.second;
            valueOfMinVertex = -1 * deletedPair.first;
            edgeListCurNode = adjList.Get(idOfMinVertex);
            for (itr = edgeListCurNode.begin(); itr != edgeListCurNode.end(); itr++)
            {
                alt = valueOfMinVertex + itr->getImport();
                idOfCurTailVertex = itr->getTailNode().getVid();
                if (alt < distTable.Get(idOfCurTailVertex))
                {
                    distTable.Insert(idOfCurTailVertex, alt);
                    pq.push(make_pair(-1 * alt, idOfCurTailVertex));
                    pathTable.Insert(idOfCurTailVertex, idOfMinVertex);
                }
            }
        }
        for (curNode = destNode; 
        curNode.getVid() != pathTable.Get(curNode.getVid()); 
        resultList.insert(resultList.begin(), curNode.getCountry()), curNode = nodeTable.Get(pathTable.Get(curNode.getVid())));
        resultList.insert(resultList.begin(), curNode.getCountry());
        delete [] validKeys;
        return resultList;
    }
    else
    {
        delete [] validKeys;
        return resultList;
    }
}

int Graph::recIsCyclic(const Node &startNode, list<Node> prevPath)
{
    int curStatus;
    list<Edge> adjacentList;
    list<Edge>::iterator itrEdges;
    list<Node>::iterator itrPath;
    adjacentList = adjList.Get(startNode.getVid());
    for (itrEdges = adjacentList.begin(); itrEdges != adjacentList.end(); itrEdges++)
    {
        for (itrPath = prevPath.begin(); itrPath != prevPath.end(); itrPath++)
        {
            if (itrEdges->getTailNode().getVid() == itrPath->getVid())
            {
                return 1;
            }
        }
    }
    prevPath.insert(prevPath.end(), startNode);
    for (itrEdges = adjacentList.begin(); itrEdges != adjacentList.end(); itrEdges++)
    {
        curStatus = recIsCyclic(itrEdges->getTailNode(), prevPath);
        if (curStatus == 1)
        {
            return 1;
        }
    }
    return 0;
}

bool Graph::isCyclic() {
    // TODO: IMPLEMENT THIS FUNCTION.
    int *validKeys = new int[nodeTable.Size()];
    int i, curStatus;
    list<Node> emptyList;
    nodeTable.getKeys(validKeys);
    if (validKeys != NULL)
    {
        for (i = 0; i < nodeTable.Size(); i++)
        {
            curStatus = recIsCyclic(nodeTable.Get(validKeys[i]), emptyList);
            if (curStatus == 1)
            {
                delete [] validKeys;
                return true;
            }
        }
        delete [] validKeys;
        return false;
    }
    else
    {
        delete [] validKeys;
        return false;
    }
}


list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    // TODO: IMPLEMENT THIS FUNCTION.
    queue<Node> queueOfBFS;
    list<string> returnList;
    list<string> emptyList;
    list<Edge> curAdjList;
    list<Edge>::iterator adjListItr;
    HashTable<int, bool> visitedTable;
    int i;
    int *validKeys = new int[nodeTable.Size()];
    nodeTable.getKeys(validKeys);
    if (validKeys != NULL)
    {
        for (i = 0; i < nodeTable.Size(); i++)
        {
            visitedTable.Insert(validKeys[i], false);
        }
        queueOfBFS.push(srcNode);
        visitedTable.Insert(srcNode.getVid(), true);
        while (!queueOfBFS.empty())
        {
            returnList.insert(returnList.end(), queueOfBFS.front().getCountry());
            if (queueOfBFS.front().getVid() == destNode.getVid())
            {
                delete [] validKeys;
                return returnList;
            }
            curAdjList = adjList.Get(queueOfBFS.front().getVid());
            queueOfBFS.pop();
            for (adjListItr = curAdjList.begin(); adjListItr != curAdjList.end(); adjListItr++)
            {
                if (visitedTable.Get(adjListItr->getTailNode().getVid()) == false)
                {
                    visitedTable.Insert(adjListItr->getTailNode().getVid(), true);
                    queueOfBFS.push(adjListItr->getTailNode());
                }
            }
        }
        delete [] validKeys;
        return emptyList;
    }
    else
    {
        delete [] validKeys;
        return emptyList;
    }
}