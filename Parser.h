#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"

enum kindNode { ADD, MULTI, PRIMER, OPEN_SEP};

class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	Token* t;

	//kindNode detKindNode(Node*);
	kindNode detKindNode(Token*);

	void toChild(Node *parent, Node *child)
	{
		child->parent = parent;
		parent->addChild(child);
	}
	void nextToken()
	{
		t = lexer->nextToken();
	}
public:
	Parser(Lexer *l) : bufferNode(NULL), lexer(l), t(NULL)
	{
		t = lexer->nextToken();
	}
	
	Node* createNode()
	{
		Node* n = new Node(t);
		nextToken();
		return n;
	}

	Node* addNodeInTree(Token*);
	Node* parsAdd();
	Node* parsMulti();
	Node* parsPrim();
};

#endif // PARSER_H