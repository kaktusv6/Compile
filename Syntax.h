#ifndef SYNTAXER_H
#define SYNTAXER_H
#include "Node.h"

enum kindNode {ADD, MULTI, PRIMER};
class Syntaxer
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
	Syntaxer() : currentNode(NULL)
	{}
	
	Node* addNodeInTree(Token*);
};

#endif // SYNTAXER_H