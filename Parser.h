#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"

enum kindExpr {
	ADD, MULTI, PRIMER, OPEN_SEP, CLOSE_SEP,
	RELAT, UNARY, ERR, END_EXPR, VARAIABLE
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

	bool isPrimer(Token* tok)
	{
		if (t == NULL) return false;
		string token = tok->getToken();
		if (token == "integer" || token == "ident" ||
			token == "string" || token == "real" || token == "char")
			return true;

		return false;
	}
	bool isUnary(Token* tok)
	{
		if (t == NULL) return false;
		string lexText = tok->getLexText();
		return lexText == "+" || lexText == "-" || lexText == "not";
	}
	bool isMulti(Token* tok)
	{
		if (t == NULL) return false;
		string lexText = tok->getLexText();

		return lexText == "*" || lexText == "/" ||
			lexText == "div" || lexText == "mod" ||
			lexText == "in" || lexText == "and";
	}
	bool isAdd(Token* tok)
	{
		if (t == NULL) return false;
		string lexText = tok->getLexText();

		return lexText == "+" || lexText == "-" ||
			lexText == "or";
	}
	bool isRelat(Token* tok)
	{
		if (t == NULL) return false;
		string lexText = tok->getLexText();

		return lexText == "<" || lexText == "<=" ||
			lexText == "<>" || lexText == ">=" || lexText == ">" ||
			lexText == "=";
	}
	bool isVaraile(Token* tok)
	{
		if (t == NULL) return false;
		string token = tok->getToken();

		return token == "ident";
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
	Node parsVaraible();
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