#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"

enum kindOp { ADD, MULTI, PRIMER, OPEN_SEP,
	CLOSE_SEP, RELAT, UNARY };

class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	Token* t;

	kindOp detKindOp(Token*);

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
	bool isPrimer(Token* tok)
	{
		string token = tok->getToken();
		if (token == "integer" || token == "ident" ||
			token == "string" || token == "real" || token == "char")
			return true;

		return false;
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