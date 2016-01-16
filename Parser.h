#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"

enum kindNode { ADD, MULTI, PRIMER, OPEN_SEP,
	CLOSE_SEP, RELAT, UNARY };

class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	Token* t;

	kindNode detKindOp(Token*);

	Token* nextToken()
	{
		t = lexer->nextToken();
		return t;
	}
	bool isUnary(Token* tok)
	{
		string lexText = tok->getLexText();
		return lexText == "+" || lexText == "-" || lexText == "not";
	}
public:
	Parser(Lexer *l) : currentNode(NULL), lexer(l), t(NULL)
	{
		t = lexer->nextToken();
	}

	Node* createNode()
	{
		Node* n = new Node(t);
		nextToken();
		return n;
	}
	Node* createNode(Node* c)
	{
		Node* n = new Node(t);
		n->addChild(c);
		nextToken();
		return n;
	}

	Node* parsRelat();
	Node* parsAdd();
	Node* parsMulti();
	Node* parsUnary();
	Node* parsPrim();
};

#endif // PARSER_H