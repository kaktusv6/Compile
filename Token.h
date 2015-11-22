#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int amountKeywords = 24;
const int amountOperation = 25;
const int amountSeparators = 8;

map <string, string> keywordsToken{
	{ "begin", "keyword" },
	{ "forward", "keyword" },
	{ "do", "keyword" },
	{ "else", "keyword" },
	{ "end", "keyword" },
	{ "for", "keyword" },
	{ "function", "keyword" },
	{ "if", "keyword" },
	{ "array", "keyword" },
	{ "of", "keyword" },
	{ "procedure", "keyword" },
	{ "program", "keyword" },
	{ "record", "keyword" },
	{ "then", "keyword" },
	{ "to", "keyword" },
	{ "type", "keyword" },
	{ "var", "keyword" },
	{ "while", "keyword" },
	{ "break", "keyword" },
	{ "continue", "keyword" },
	{ "downto", "keyword" },
	{ "exit", "keyword" },
	{ "repeat", "keyword" },
	{ "until", "keyword" }
};

map<string, string> operationToken = {
	{ "and", "op" },
	{ "div", "op" },
	{ "mod", "op" },
	{ "not", "op" },
	{ "or", "op" },
	{ "xor", "op" },
	{ "+", "op" },
	{ "-", "op" },
	{ "*", "op" },
	{ "/", "op" },
	{ "^", "op" },
	{ "+=", "op" },
	{ "-=", "op" },
	{ "*=", "op" },
	{ "/=", "op" },
	{ "<", "op" },
	{ ">", "op" },
	{ "<=", "op" },
	{ ">=", "op" },
	{ "=", "op" },
	{ "<", "op" },
	{ ">", "op" },
	{ ":=", "op" },
	{ "@", "op" },
	{ ".", "op" }
};

string separatorsToken[amountSeparators] = {
	"(",
	")",
	"[",
	"]",
	";",
	",",
	":",
	"..",
};

class Token
{
private:
	string token;
public:
	Token(); // конструктор класса

	void checkKeyword(string lexText);
	void checkOperation(string lexText);
	//void lexemToToken(string s);
};

