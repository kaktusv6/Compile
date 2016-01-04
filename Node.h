#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>
#include <list>

using namespace std;

enum kind
{
	REALAT_OP, ADD_OP, UNARY_OP, MULTI_OP,
	PRIM_EXPR, ADD_EXPR, UNARY_EXPR, MULTI_EXPR, EXPR
};

class Node
{
private:
	string expression;
	list<Node*> child;
	kind kindNode;
	Node *parent;

public:
	Node() : kindNode(EXPR), expression(NULL), parent(NULL)
	{  }

	Node(string s, kind k) : kindNode(k), expression(s), parent(NULL)
	{  }

	void setExpression(string s) { this->expression = s; }

	void setParent(Node *n) { this->parent = n; }

	string getExpression() { return this->expression; }

	Node* getParent() { return this->parent; }
};

#endif // NODE