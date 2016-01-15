#include "Parser.h"


kindNode Parser::detKindNode(Node *n)
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
kindNode Parser::detKindNode(Token *tok)
{
	string
		token = tok->getToken(),
		lexText = tok->getLexText();

	if (lexText == "*" || lexText == "/")
		return MULTI;
	if (lexText == "+" || lexText == "-")
		return ADD;
	if (token == "integer")
		return PRIMER;
}


Node* Parser::parsPrim()
{
	//if createNode(t) == PRIM
	return createNode();
}

Node* Parser::parsMulti()
{
	Node* n = parsPrim();
	Node* current = NULL;
	while (true)
	{
		if (t != NULL && detKindNode(t) == MULTI)
		{
			current = createNode();
			current->addChild(n);
			current->addChild(parsPrim());
			n = current;
		}
		else
		{
			if (current != NULL)
				return current;

			return n;
		}
	}
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	Node* current = NULL;
	while (true)
	{
		if (t != NULL && detKindNode(t) == ADD)
		{
			current = createNode();
			current->addChild(n);
			current->addChild(parsMulti());
			n = current;
		}
		else
		{
			if (current != NULL)
				return current;

			return n;
		}
	}
}