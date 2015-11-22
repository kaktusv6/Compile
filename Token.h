#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

const int amountKeywords = 24;
const int amountOperation = 25;
const int amountSeparators = 8;

class Token
{
private:
	string token;

	map <string, string> keywordsToken{
		{"begin" , "keyword"},
		{"forward" , "keyword"},
		{"do" , "keyword"},
		{"else" , "keyword"},
		{"end" , "keyword"},
		{"for" , "keyword"},
		{"function" , "keyword"},
		{"if" , "keyword"},
		{"array" , "keyword"},
		{"of" , "keyword"},
		{"procedure" , "keyword"},
		{"program" , "keyword"},
		{"record" , "keyword"},
		{"then" , "keyword"},
		{"to" , "keyword"},
		{"type" , "keyword"},
		{"var" , "keyword"},
		{"while" , "keyword"},
		{"break" , "keyword"},
		{"continue" , "keyword"},
		{"downto" , "keyword"},
		{"exit" , "keyword"},
		{"repeat" , "keyword"},
		{ "until" , "keyword" }
	};

	map<string, string> operationToken = {
		{"and" , "op" },		
		{"div" , "op" },		
		{"mod" , "op" },		
		{"not" , "op" },		
		{"or" , "op" },		
		{"xor" , "op" },		
		{"+" , "op" },		
		{"-" , "op" },		
		{"*" , "op" },
		{"/" , "op" },		
		{"^" , "op" },		
		{"+=" , "op" },		
		{"-=" , "op" },		
		{"*=" , "op" },		
		{"/=" , "op" },		
		{"<" , "op" },		
		{">" , "op" },		
		{"<=" , "op" },		
		{">=" , "op" },
		{"=" , "op" },		
		{"<" , "op" },		
		{">" , "op" },		
		{":=" , "op" },		
		{"@" , "op" },		
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

public:
	Token(); // конструктор класса

	string checkKeyword(string lexText);
	//void lexemToToken(string s);
};

