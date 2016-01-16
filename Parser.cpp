#include "Parser.h"

//kindNode Parser::detKindNode(Node *n)
//{
//	string
//		token = n->getTokenNode()->getToken(),
//		lexText = n->getTokenNode()->getLexText();
//
//	if (lexText == "*" || lexText == "/")
//		return MULTI;
//	if (lexText == "+" || lexText == "-")
//		return ADD;
//	if (token == "integer")
//		return PRIMER;
//}
kindNode Parser::detKindNode(Token *tok)
{
	string
		token = tok->getToken(),
		lexText = tok->getLexText();

	if (lexText == "*" || lexText == "/" ||
		lexText == "div" || lexText == "mod")
		return MULTI;
	if (lexText == "+" || lexText == "-")
		return ADD;
	if (token == "integer" || token == "ident" ||
		token == "string" || token == "real")
		return PRIMER;
	if (lexText == "(")
		return OPEN_SEP;
}

Node* Parser::parsPrim()
{
	if (detKindNode(t) == PRIMER)
		return createNode();
	if (detKindNode(t) == OPEN_SEP)
	{
		nextToken();
		Node* n = parsAdd();
		nextToken();
		return n;
	}
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