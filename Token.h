#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

const int amountKeywords = 24;

class Token
{
private:
	//enum token {ID, OP, BEGIN, FORWARD, DO, ELSE, END, FOR, FUNCTION, IF, ARRAY, OF, PROCEDURE, PROGRAM, RECORD, THEN, TO, TYPE, VAR, WHILE, BREAK, CONTINUE, DOWNTO, EXIT, REPEAT, UNTIL };
	//token tok;
	string token;

	//map <string, token> keywordsMap;

	string keywords[amountKeywords] = {
		 "begin", "forward", "do", "else", "end", "for", "function", "if", "array", "of", "procedure", "program", "record", "then", "to", "type", "var", "while", "break", "continue", "downto", "exit", "repeat", "until
	};
	//string stringToken;
	//string tokenOperation[25] = { "and", "div", "mod", "not", "or", "xor", "+", "-", "*", "/", "^", "+=", "-=", "*=", "/=", "<", ">", "<=", ">=", "=", "<", ">", ":=", "@", "."};

public:
	Token(); // конструктор класса

	void lexemToToken(string s);
	string tokenToString();
};

