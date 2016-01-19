#include "Parser.h"

Node* Parser::parsVaraible()
{
	Node* n = createNode();
	if (t == NULL)
		return n;

	if (t->getLexText() == "[")
	{
		nextToken();
		n->addChild(parsRelat());
		if (t != NULL)
		{
			if (t->getLexText() == "]")
				nextToken();
		}
		else
			throw SynError(t, " No closing parenthesis");
	}
	else if (t->getLexText() == "^")
		n = createNode(n);
	if (t->getLexText() == ".")
	{
		Node* c = n;
		n = createNode();
		n->addChild(parsVaraible())->addChild(c);
	}

	return n;
}

Node* Parser::parsPrim()
{
	try
	{
		if (t == NULL)
			throw SynError(t, " No primary-expression");

		if (isPrimer())
			return createNode();
		else if (isVaraile())
		{
			return parsVaraible();
		}
		else if (t->getLexText() == "(")
		{
			nextToken();
			Node* n = parsRelat();
			if (t != NULL)
			{
				if (t->getLexText() == "]")
					nextToken();
			}
			else
				throw SynError(t, " No closing parenthesis");
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
		if (isUnary())
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
	while (t != NULL && isMulti())
	{
		n = createNode(n);
		n->addChild(parsUnary());
	}
	return n;
}

Node* Parser::parsAdd()
{
	Node* n = parsMulti();
	while (t != NULL && isAdd())
	{
		n = createNode(n);
		n->addChild(parsMulti());
	}
	return n;
}

Node* Parser::parsRelat()
{
	Node* n = parsAdd();
	while (t != NULL && isRelat())
	{
		n = createNode(n);
		n->addChild(parsAdd());
	}
	return n;
}