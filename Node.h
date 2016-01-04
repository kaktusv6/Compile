#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>
#include <list>

using namespace std;

class Node
{
private:
	string expression;
	list<Node*> child;
	//Node *left;
	//Node *right;
	Node *parent;

public:
	Node() : expression(NULL), parent(NULL)
	{}

	Node(string s) : parent(NULL)
	{
		expression = s;
	}

	void setExpression(string s) { this->expression = s; }

	void setParent(Node *n) { this->parent = n; }

	string getExpression() { return this->expression; }

	Node* getParent() { return this->parent; }
};

#endif // NODE