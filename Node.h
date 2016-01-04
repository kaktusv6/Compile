#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>
#include <list>

using namespace std;

class Node
{
private:
	Token *expression;
	list<Node*> child;
	//Node *left;
	//Node *right;
	Node *parent;

public:
	Node() : expression(NULL), parent(NULL)
	{}

	Node(Token *t) : parent(NULL)
	{
		expression = t;
	}

	void setExpression(Token* t) { this->expression = t; }

	void setParent(Node *n) { this->parent = n; }

	Token* getExpression() { return this->expression; }

	Node* getParent() { return this->parent; }
};

#endif // NODE