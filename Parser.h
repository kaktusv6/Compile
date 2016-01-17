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

enum kindError {NO_CLOSE_SEP, NO_PRIMER, NOT_UNARY_EXPR};

class SynError
{
private:
	kindError err;
public:
	SynError()
	{}
	SynError(kindError e) : err(e)
	{}
	void printError()
	{
		if (err == NO_CLOSE_SEP)
		{
			cout << "No closing parenthesis" << endl;
			system("pause");
			exit(1);
		}
		else if (err == NO_PRIMER)
		{
			cout << "No primary-expression" << endl;
			system("pause");
			exit(1);
		}
	}
};
#endif // PARSER_H