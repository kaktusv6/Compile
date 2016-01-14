#include "Syntax.h"


kindNode Syntax::detKindNode(Node *n)
{
	if (n->getTokenNode()->getLexText() == "*" 
		|| n->getTokenNode()->getLexText() == "/")
		return MULTI;
	if (n->getTokenNode()->getLexText() == "+"
		|| n->getTokenNode()->getLexText() == "-")
		return ADD;
	if (n->getTokenNode()->getToken() == "integer")
		return PRIMER;
}

Node* Syntax::takeToken(Token* t)
{
	Node *n = new Node(t);
	if (t->getToken() == "integer")
	{
		if (currentNode == NULL) currentNode = n;
		else if (currentNode != NULL)
		{
			n->parent = currentNode;
			currentNode->addChild(n);
		}
	}
	else if (t->getToken() == "op")
	{
		if (currentNode == NULL) currentNode = n;
		else if (currentNode != NULL)
		{
			currentNode->parent = n;
			n->addChild(currentNode);
			currentNode = n;
		}
	}
	return n;
}