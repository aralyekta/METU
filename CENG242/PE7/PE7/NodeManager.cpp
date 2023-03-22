
#include "NodeManager.h"

NodeManager::NodeManager() {
	// TODO
}

NodeManager::~NodeManager() {
	vector<Node*>::iterator itr = trees.begin();
	for(; itr != trees.end(); itr++)
	{
		delete *itr;
	}
}

void NodeManager::addRelation(int parent, int child) {
	Node *parentNode = NULL, *childNode = NULL;
	vector<Node*>::iterator itr = trees.begin();
	bool findParent = false, findChild = false;
	vector<Node*>::iterator childItr;
	for(; itr != trees.end(); itr++)
	{
		if ((*itr)->getId() == parent)
		{
			findParent = true;
			parentNode = (*itr);
		}
		if ((*itr)->getId() == child)
		{
			findChild = true;
			childNode = (*itr);
			childItr = itr;
			trees.erase(itr);
			break;
		}
	}
	if (!findParent)
	{
		for (itr = trees.begin(); itr != trees.end(); itr++)
		{
			parentNode = findNode(parent, *itr);
			if (parentNode)
			{
				findParent = true;
				break;
			}
		}
		if (!findParent)
		{
			parentNode = new Node(parent);
			trees.insert(trees.end(), parentNode);
		}

	}
	if (!findChild)
	{
		for (itr = trees.begin(); itr != trees.end(); itr++)
		{
			childNode = findNode(child, *itr);
			if (childNode)
			{
				findChild = true;
				break;
			}
		}
		if (!findChild)
		{
			childNode = new Node(child);
		}
	}
	(*parentNode) += (*childNode);
}

void NodeManager::setDataToNode(int id, char data) {
	Node *searchedNode = NULL;
	Node *searchedParent = NULL;
	DataNode *createdNode = NULL;
	vector<Node*>::iterator itrChild;
	vector<Node*>::iterator itrParent;
	vector<Node*>::iterator itr;
	for (itrChild = trees.begin(); itrChild != trees.end(); itrChild++)
	{
		searchedNode = findNode(id, *itrChild);
		if (searchedNode)
		{
			break;
		}
	}
	if (searchedNode) //Node exists
	{
		for (itrParent = trees.begin(); itrParent != trees.end(); itrParent++)
		{
			searchedParent = findParent(id, *itrParent);
			if (searchedParent)
			{
				break;
			}
		}
		createdNode = new DataNode(*searchedNode, data);
		if (searchedParent) //Node is not root
		{
			for (itr = searchedParent->getChildren().begin(); itr != searchedParent->getChildren().end(); itr++)
			{
				if ((*itr)->getId() == id)
				{
					searchedParent->getChildren().erase(itr);
					break;
				}
			}
			searchedParent->getChildren().push_back(createdNode);
		}
		else //Node is root
		{
			trees.erase(itrChild);
			trees.push_back(createdNode);
		}
		delete searchedNode;
	}
	else //Node does not exist
	{
		createdNode = new DataNode(id, data);
		trees.push_back(createdNode);
	}
}

const Node& NodeManager::getNode(int id) {
	Node *result;
	vector<Node*>::iterator itr = trees.begin();
	for (; itr != trees.end(); itr++)
	{
		result = findNode(id, *itr);
		if (result)
		{
			return *result;
		}
	}
}

Node*NodeManager::findParent(int id, Node *ptr)
{
	Node *result;
	vector<Node*>::iterator itr;
	for (itr = (ptr->getChildren()).begin(); itr != (ptr->getChildren()).end(); itr++)
	{
		if ((*itr)->getId() == id)
		{
			return ptr;
		}
	}
	for (itr = (ptr->getChildren()).begin(); itr != (ptr->getChildren()).end(); itr++)
	{
		result = findParent(id, *itr);
		if (result)
		{
			return result;
		}
	}
	return NULL;
}

Node *NodeManager::findNode(int id, Node *ptr)
{
	Node *result;
	vector<Node*>::iterator itr = (ptr->getChildren()).begin();
	if (ptr->getId() == id)
	{
		return ptr;
	}
	for (; itr != (ptr->getChildren()).end(); itr++)
	{
		result = findNode(id, *itr);
		if (result)
		{
			return result;
		}
	}
	return NULL;
}