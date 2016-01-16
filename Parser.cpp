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
		lexText == "div" || lexText == "mod" || lexText == "in")
		return MULTI;
	if (lexText == "+" || lexText == "-" ||
		lexText == "or")
		return ADD;
	if (token == "integer" || token == "ident" ||
		token == "string" || token == "real" || token == "char")
		return PRIMER;
	if (lexText == "<" || lexText == "<=" ||
		lexText == "<>" || lexText == ">=" || lexText == ">" ||
		lexText == "=")
		return RELAT;
	if (lexText == "(")
		return OPEN_SEP;
	if (lexText == ")")
		return CLOSE_SEP;
}

Node* Parser::parsPrim()
{
	if (detKindNode(t) == PRIMER)
		return createNode();
	if (detKindNode(t) == OPEN_SEP)
	{
		nextToken();
		Node* n = parsRelat();
		//if (!detKindNode(t) == CLOSE_SEP){
		//	//throw SynError();
		//}
		nextToken();
		return n;
	}
}

Node* Parser::parsUnary()
{
	if (isUnary(t))
	{
		Node *n = createNode();
		while (t != NULL && isUnary(t))
		{
			n = createNode(n);
		}
		n->addChild(parsPrim());
		return n;
	}
	return parsPrim();
}

Node* Parser::parsMulti()
{
	Node* n = parsUnary();
	while (t != NULL && detKindNode(t) == MULTI)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	while (t != NULL && detKindNode(t) == ADD)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && detKindNode(t) == RELAT)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}