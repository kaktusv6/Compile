#include "Parser.h"

kindExpr Parser::detKindToken(Token *tok)
{
	if (t == NULL)
		return END_EXPR;

	string
		lexText = tok->getLexText();
	if (lexText == "[")
		return VAR_OPEN_SEP;
	
	if (lexText == "]")
		return VAR_CLOSE_SEP;

	if (lexText == "(")
		return OPEN_SEP;

	if (lexText == ")")
		return CLOSE_SEP;
}

Node* Parser::parsVaraible()
{
	Node* n = createNode();
	if (t == NULL)
		return n;

	if (detKindToken(t) == VAR_OPEN_SEP)
	{
		nextToken();
		n->addChild(parsRelat());
		if (detKindToken(t) != VAR_CLOSE_SEP)
			throw SynError(t, " No closing parenthesis");
		nextToken();
	}
	else if (t->getLexText() == "^")
		n = createNode(n);

	return n;
}

Node* Parser::parsPrim()
{
	try
	{
		kindExpr k = detKindToken(t);
		if (isPrimer(t))
			return createNode();
		else if (isVaraile(t))
		{
			return parsVaraible();
		}
		else if (k == OPEN_SEP)
		{
			nextToken();
			Node* n = parsRelat();
			if (detKindToken(t) != CLOSE_SEP)
				throw SynError(t, " No closing parenthesis");
			nextToken();
			return n;
		}
		else
			throw SynError(t, " No primary-expression");
	}
	catch (SynError e)
	{
		e.printError();
	}
}

Node* Parser::parsUnary()
{
		if (isUnary(t))
		{
			Node *n = createNode();
			n->addChild(parsUnary());
			return n;
		}
		return parsPrim();
}

Node* Parser::parsMulti()
{
	Node* n = parsUnary();
	while (t != NULL && isMulti(t))
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	while (t != NULL && isAdd(t))
	{
		n = createNode(n);
		n->addChild(parsMulti());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && isRelat(t))
	{
		n = createNode(n);
		n->addChild(parsAdd());
	}
	return n;
}