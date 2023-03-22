#include "Action.h"
#include "Exception.h"

Action::Action() {
	result = new Node(5);
	ptr1 = NULL;
}

Action::~Action() {
	delete result;
}

/********************** CompleteAction **************************/

CompleteAction::CompleteAction(const Node& node) {
	const Node *ptr = &node;
	ptr1 = ptr;
}

CompleteAction::~CompleteAction() {
	delete result;
}

Node* CompleteAction::act(const Node* node) const {
	bool DN1 = false, DN2 = false;
	try
	{
		ptr1->getData();
		DN1 = true;
	}
	catch (InvalidRequest e)
	{
		DN1 = false;
	}
	try
	{
		node->getData();
		DN2 = true;
	}
	catch (InvalidRequest e)
	{
		DN2 = false;
	}
	if (!DN2)
	{
		Node *result2 = ((*node) & (*ptr1));
		*result = *result2;
	}
	else if (!DN1)
	{
		Node *result2 = ((*ptr1) & (*node));
		*result = *result2;
	}
	else
	{
		Node *result2 = ((*node) & (*ptr1));
		*result = *result2;
	}
}

/************************* CutAction ***************************/

CutAction::CutAction(char character) {
	// TODO
}

CutAction::~CutAction() {
	// TODO
}

Node* CutAction::act(const Node* node) const {
	// TODO
}

/************************* CompositeAction ***************************/

CompositeAction::CompositeAction() {
	// TODO
}

CompositeAction::~CompositeAction() {
	// TODO
}

CompositeAction* CompositeAction::addAction(const Action* action) {
	// TODO
}

Node* CompositeAction::act(const Node* node) const {
	// TODO
}