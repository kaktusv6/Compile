#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>

using namespace std;

class Node
{
private:
	Token *expression;
	Node *left;
	Node *right;
	Node *parent;

public:
	Node() : expression(NULL), left(NULL), right(NULL), parent(NULL)
	{}

	Node(Token *t) : left(NULL), right(NULL), parent(NULL)
	{
		expression = t;
	}

	void setExpression(Token* t) { this->expression = t; }
	void setLeft  (Node *n) { this->left = n; }
	void setRight (Node *n) { this->right = n; }
	void setParent(Node *n) { this->parent = n; }

	Token* getExpression() { return this->expression; }
	Node* getLeft() { return this->left; }
	Node* getRight() { return this->right; }
	Node* getParent() { return this->parent; }
};

#endif // NODE