#include "Syntax.h"

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