#include "Node.h"

// // // THE FRIEND METHODS ARE ALREADY IMPLEMENTED. // // //
// // // // // // // DO NOT CHANGE THEM! // // // // // // //

Node::Node(int id) {
	this->id = id;
}

Node::~Node() {
	vector<Node*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++)
	{
		delete *itr;
	}
}

Node::Node(const Node& node) {
	id = node.id;
	Node *createdNode;
	vector<Node*> rightChildren = node.children;
	vector<Node*>::iterator itr = rightChildren.begin();
	for (; itr != rightChildren.end(); itr++)
	{
		createdNode = new Node(**itr);
		children.push_back(createdNode);
	}
}

int Node::getId() const {
	return id;
}

char Node::getData() const {
	throw InvalidRequest();
}

vector<Node*>& Node::getChildren() {
	return children;
}

void Node::operator+=(Node& childNode) {
	children.push_back(&childNode);
}

Node* Node::operator&(const Node& node) const {
	Node *createdN;
	Node *result;
	Node *result1;
	Node *result2;
	DataNode *createdDN;
	bool DN1 = false, DN2 = false;
	bool DN1inner = false, DN2inner = false;
	bool DN = false;
	vector<Node*> child1;
	vector<Node*> child2;
	vector<Node*>::iterator itr1;
	vector<Node*>::iterator itr2;
	cout << "Entered the function\n";
	cout << (*this) << " and " << node << "\n";
	try
	{
		getData();
		//If we stay here, then DN-X
		DN1 = true;
	}
	catch (InvalidRequest e) 
	{
		//If we get here, then N-X
		DN1 = false;
	}
	try 
	{
		node.getData();
		DN2 = true;
		//If we stay here, DN-DN
	}
	catch (InvalidRequest e)
	{
		DN2 = false;
		//If we get here, then it is DN-N
	}
	if (DN1)
	{
		createdDN = new DataNode(this->getId(), this->getData());
		DN = true;
	}
	else if (DN2)
	{
		createdDN = new DataNode(node.getId(), node.getData());
		DN = true;
	}
	else
	{
		createdN = new Node(this->getId());
		DN = false;
	}
	if (this->children.size() > 0 && node.children.size() > 0)
	{
		child1 = this->children;
		child2 = node.children;
		for (itr1 = child1.begin(); itr1 != child1.end(); itr1++)
		{
			cout << "ITERATING FOR: " << (**itr1) << "\n";
			for (itr2 = child2.begin(); itr2 != child2.end(); itr2++)
			{
				cout << "Iteration: \n";
				cout << (**itr1) << " and " << (**itr2) << "\n";
				if ((*itr1)->getId() == (*itr2)->getId())
				{
					try 
					{
						(*itr1)->getData();
						DN1inner = true;
					}
					catch (InvalidRequest e)
					{
						DN1inner = false;
					}
					try
					{
						(*itr2)->getData();
						DN2inner = true;
					}
					catch (InvalidRequest e)
					{
						DN2inner = false;
					}
					cout << "Accepted: " << (**itr1) << " and " << (**itr2) << " | ";
					cout << DN1inner << " " << DN2inner << "\n";
					if (!DN2inner)
					{
						result = (**itr2) & (**itr1);
					}
					else if (!DN1inner)
					{
						result = (**itr1) & (**itr2);
					}
					else
					{
						result = (**itr2) & (**itr1);
					}
					if (DN)
					{
						*createdDN += *result;
					}
					else
					{
						*createdN += *result;
					}
					break;
				}
			}
		}
	}
	if (DN)
	{
		return createdDN;
	}
	else
	{
		return createdN;
	}
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const Node& node) {
	try {
		node.getData();
		os << *(DataNode*)&node;
	}
	catch (InvalidRequest e) {
		os << "[" << node.id;
		for (int i = 0; i < node.children.size(); i++)
			os << ", " << *node.children[i];
		os << "]";
	}
	return os;
}

/*************** DataNode *****************/

DataNode::DataNode(int id, char data):Node(id) {
	this->id = id;
	this->data = data;
}

DataNode::~DataNode() {
	vector<Node*>::iterator itr;
	for (itr = children.begin(); itr != children.end(); itr++)
	{
		delete *itr;
	}
}

DataNode::DataNode(const DataNode& dataNode):Node(dataNode.getId()) {
	this->id = dataNode.id;
	this->data = dataNode.data;
	Node *createdNode;
	vector<Node*> rightChildren = dataNode.children;
	vector<Node*>::iterator itr = rightChildren.begin();
	for (; itr != rightChildren.end(); itr++)
	{
		createdNode = new Node(**itr);
		children.push_back(createdNode);
	}
}

DataNode::DataNode(const Node& node, char data):Node(node) {
	this->id = node.getId();
	this->data = data;
}

char DataNode::getData() const {
	return data;
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const DataNode& dataNode) {
	os << "[" << "(" << dataNode.id << ", \'" << dataNode.data << "\')";
	for (int i = 0; i < dataNode.children.size(); i++)
		os << ", " << *dataNode.children[i];
	os << "]";
	return os;
}
