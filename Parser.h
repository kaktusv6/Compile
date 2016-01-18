#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"

enum kindExpr {
	ADD, MULTI, PRIMER, OPEN_SEP, CLOSE_SEP,
	RELAT, UNARY, ERR, END_EXPR
};

class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	Token* t;

	kindExpr detKindToken(Token*);

	Token* nextToken()
	{
		t = lexer->nextToken();
		return t;
	}

	bool isUnary(Token* tok)
	{
		if (t == NULL) return false;
		string lexText = tok->getLexText();
		return lexText == "+" || lexText == "-" || lexText == "not";
	}
	bool isPrimer(Token* tok)
	{
		if (t == NULL) return false;
		string token = tok->getToken();
		if (token == "integer" || token == "ident" ||
			token == "string" || token == "real" || token == "char")
			return true;

		return false;
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
	
	Node* parsAdd();
	Node* parsMulti();
	Node* parsUnary();
	Node* parsPrim();
public:
	Parser(Lexer *l) : currentNode(NULL), lexer(l), t(NULL)
	{
		t = lexer->nextToken();
	}

	Node* parsRelat();
};

class SynError
{
private:
	string str;
public:
	SynError(Token* t, string s)
	{
		if (t != NULL)
			str = t->getPosition() + s;
		str = s;
	}

	void printError()
	{
		cout << str << endl;
		system("pause");
		exit(1);
	}
};
#endif // PARSER_H