#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Node.h"



class Parser
{
private:
	Node* currentNode;
	Lexer *lexer;
	Token* t;

	Token* nextToken()
	{
		t = lexer->nextToken();
		return t;
	}

	bool isPrimer()
	{
		if (t == NULL) return false;
		string token = t->getToken();
		if (token == "integer"  || token == "string" ||
			token == "real" || token == "char")
			return true;

		return false;
	}
	bool isUnary()
	{
		if (t == NULL) return false;
		string lexText = t->getLexText();
		return lexText == "+" || lexText == "-" || lexText == "not";
	}
	bool isMulti()
	{
		if (t == NULL) return false;
		string lexText = t->getLexText();

		return lexText == "*" || lexText == "/" ||
			lexText == "div" || lexText == "mod" ||
			lexText == "in" || lexText == "and";
	}
	bool isAdd()
	{
		if (t == NULL) return false;
		string lexText = t->getLexText();

		return lexText == "+" || lexText == "-" ||
			lexText == "or";
	}
	bool isRelat()
	{
		if (t == NULL) return false;
		string lexText = t->getLexText();

		return lexText == "<" || lexText == "<=" ||
			lexText == "<>" || lexText == ">=" || lexText == ">" ||
			lexText == "=";
	}
	bool isVaraile()
	{
		if (t == NULL) return false;
		string token = t->getToken();

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
		nextToken();
		n->addChild(c);
		return n;
	}
	
	Node* parsAdd();
	Node* parsMulti();
	Node* parsUnary();
	Node* parsPrim();
	Node* parsVaraible();
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