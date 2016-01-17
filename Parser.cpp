#include "Parser.h"

kindOp Parser::detKindToken(Token *tok)
{
	if (t == NULL) return END_EXPR;

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
	kindOp k = detKindToken(t);
	if (isPrimer(t))
		return createNode();
	if (k == OPEN_SEP)
	{
		nextToken();
		Node* n = parsRelat();
		if (detKindToken(t) != CLOSE_SEP)
		{
			throw SynError();
		}
		nextToken();
		return n;
	}
}

Node* Parser::parsUnary()
{
	try
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
	catch (SynError)
	{
		cout << "No closing parenthesis" << endl;
		system("pause");
		exit(1);
	}
}

Node* Parser::parsMulti()
{
	Node* n = parsUnary();
	while (t != NULL && detKindToken(t) == MULTI)
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	while (t != NULL && detKindToken(t) == ADD)
	{
		n = createNode(n);
		n->addChild(parsMulti());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && detKindToken(t) == RELAT)
	{
		n = createNode(n);
		n->addChild(parsAdd());
	}
	return n;
}