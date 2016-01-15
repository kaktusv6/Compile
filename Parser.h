#ifndef Parser_H
#define Parser_H
#include "Lexer.h"
#include "Node.h"

enum kindNode {ADD, MULTI, PRIMER};

class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	kindNode detKindNode(Node*);
	void toChild(Node *parent, Node *child)
	{
		child->parent = parent;
		parent->addChild(child);
	}
public:
	Parser(Lexer *l) : currentNode(NULL), lexer(l)
	{ }
	
	Node* addNodeInTree(Token*);
};

#endif // Parser_H