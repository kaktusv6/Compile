#include "Syntax.h"

Syntax::Syntax()
{
	node = new Node();
}

void Syntax::takeToken(Token *t)
{
	Node *n = new Node(t);

	if (t->getToken() == "integer")
	{
		if (node->getExpression() == NULL)
		{
			//node->setLeft(n);
		}
		else
		if (node->getExpression()->getToken() == "op")
		{
			//node->setRight(n);
		}

	}
	else if (t->getToken() == "op")
	{
		if (node->getExpression() == NULL)
		{
			node->setExpression(t);
		}
		else if (node->getExpression()->getToken() == "op")
		{
			//n->setLeft(node);
			node->setParent(n);
			node = n;
		}
	}
}