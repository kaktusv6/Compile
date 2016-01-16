#include "Parser.h"

kindNode Parser::detKindOp(Token *tok)
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
	if (detKindOp(t) == PRIMER)
		return createNode();
	if (detKindOp(t) == OPEN_SEP)
	{
		nextToken();
		Node* n = parsRelat();
		//if (!detKindOp(t) == CLOSE_SEP){
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
	while (t != NULL && detKindOp(t) == MULTI)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	while (t != NULL && detKindOp(t) == ADD)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && detKindOp(t) == RELAT)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}