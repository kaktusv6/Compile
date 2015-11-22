#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int amountKeywords = 24;
const int amountOperation = 25;
const int amountSeparators = 8;

string keywordsToken[amountKeywords] = {
	"begin",
	"forward",
	"do",
	"else",
	"end",
	"for",
	"function",
	"if",
	"array",
	"of",
	"procedure",
	"program",
	"record",
	"then",
	"to",
	"type",
	"var",
	"while",
	"break",
	"continue",
	"downto",
	"exit",
	"repeat",
	"until"
};

string operationToken[amountOperation] = {
	"and",
	"div",
	"mod",
	"not",
	"or",
	"xor",
	"+",
	"-",
	"*",
	"/",
	"^",
	"+=",
	"-=",
	"*=",
	"/=",
	"<",
	">",
	"<=",
	">=",
	"=",
	"<",
	">",
	":=",
	"@",
	"."
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

