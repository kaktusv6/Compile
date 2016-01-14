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
	if (currentNode == NULL)
	{
		if (detKindNode(n) == PRIMER)
			currentNode = n;
	}
	else if (t->getToken() == "integer")
	{
		toChild(currentNode, n);
	}
	else if (t->getToken() == "op")
	{
		toChild(n, currentNode);
		currentNode = n;
	}
	return currentNode;
}