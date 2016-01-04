#include "Syntax.h"
Syntax::Syntax()
{
	node = new Node();
}

void Syntax::takeToken(Token *t)
{
	Node *n = new Node(t);

	if (t->getToken() == "integer" && node->getExpression() == NULL)
	{
		node->setLeft(n);
	}
	else if (t->getToken() == "op" && node->getExpression() == NULL)
	{
		node->setExpression(t);
	}
	else if (t->getToken() == "integer" &&
				node->getExpression()->getToken() == "op")
	{
		node->setRight(n);
	}
}