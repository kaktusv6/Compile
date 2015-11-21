#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Token
{
private:
	enum token {ID, OP, BAD, BEGIN, FORWARD, DO, ELSE, END, FOR, FUNCTION, IF, ARRAY, OF, PROCEDURE, PROGRAM, RECORD, THEN, TO, TYPE, VAR, WHILE, BREAK, CONTINUE, DOWNTO, EXIT, REPEAT, UNTIL };
	token tok;
	
	map <string, token> keywordsMap;
	
	//string stringToken;
	//string tokenOperation[25] = { "and", "div", "mod", "not", "or", "xor", "+", "-", "*", "/", "^", "+=", "-=", "*=", "/=", "<", ">", "<=", ">=", "=", "<", ">", ":=", "@", "."};

public:
	Token(); // конструктор класса

	void lexemToToken(string s);
	string tokenToString();
};

