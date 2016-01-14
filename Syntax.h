#ifndef SYNTAXER_H
#define SYNTAXER_H
#include "Node.h"

enum kindNode {ADD, MULTI, PRIMER};
class Syntax
{
private:
	Node* currentNode;

	kindNode detKindNode(Node*);
	void toChild(Node *parent, Node *child)
	{
		child->parent = parent;
		parent->addChild(child);
	}
public:
	Syntax() : currentNode(NULL)
	{}
	
	Node* takeToken(Token*);
};

#endif // SYNTAXER_H