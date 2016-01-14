#include "Syntax.h"


kindNode Syntax::detKindNode(Node *n)
{
	string
		token = n->getTokenNode()->getToken(),
		lexText = n->getTokenNode()->getLexText();

	if (lexText == "*" || lexText == "/")
		return MULTI;
	if (lexText == "+" || lexText == "-")
		return ADD;
	if (token == "integer")
		return PRIMER;
}

Node* Syntax::takeToken(Token* t)
{
	Node *n = new Node(t);
	if (currentNode == NULL)
	{
		//if (detKindNode(n) == PRIMER)
			currentNode = n;
	}
	else if (detKindNode(n) == PRIMER)
	{
		toChild(currentNode, n);
	}
	else if (t->getToken() == "op")
	{
		kindNode
			kindCurrentNode = detKindNode(currentNode),
			kindNewNode = detKindNode(n);

		if (kindCurrentNode == PRIMER)
		{
			toChild(n, currentNode);
			currentNode = n;
		}
		else if (kindNewNode == ADD)
		{
			if (kindCurrentNode == MULTI && currentNode->parent != NULL)
			{
				Node *c = currentNode;
				while (detKindNode(c) != ADD)
				{
					c = c->parent;
				}

				toChild(n, c);
				currentNode = n;
			}
			else
			{
				toChild(n, currentNode);
				currentNode = n;
			}
		}
		else if (kindNewNode == MULTI)
		{
			if (kindCurrentNode == MULTI)
			{
				toChild(n, currentNode);
				currentNode = n;
			}
			else if (kindCurrentNode == ADD)
			{
				Node *child = currentNode->child[1];
				child->parent = n;
				n->addChild(child);

				n->parent = currentNode;
				currentNode->child[1] = n;
				currentNode = n;
			}
		}
	}
	return currentNode;
}