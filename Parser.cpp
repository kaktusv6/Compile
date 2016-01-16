#include "Parser.h"

kindOp Parser::detKindOp(Token *tok)
{
	string
		lexText = tok->getLexText();

	if (lexText == "*" || lexText == "/" ||
		lexText == "div" || lexText == "mod" ||
		lexText == "in" || lexText == "and")
		return MULTI;

	if (lexText == "+" || lexText == "-" ||
		lexText == "or")
		return ADD;

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
	kindOp k = detKindOp(t);
	if (isPrimer(t))
		return createNode();
	if (k == OPEN_SEP)
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
		n->addChild(parsMulti());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && detKindOp(t) == RELAT)
	{
		n = createNode(n);
		n->addChild(parsAdd());
	}
	return n;
}