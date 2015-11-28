#include "Token.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Token::Token()
{

}

void Token::checkKeyword(string lexText)
{
	map<string, string>::iterator i = keywordsToken.find(lexText);
	if (i != keywordsToken.end()) tokenString = i->second;
	else tokenString = "ident";
}

void Token::checkOperation(string lexText)
{
	map<string, string>::iterator i = operationToken.find(lexText);
	if (i != operationToken.end()) tokenString = i->second;
	else tokenString = "BadChar";
}

void Token::checkString(string lexText) {
	if (lexText.length() == 1)
	{
		tokenString = "char";
	}
	else
	{
		size_t found = lexText.find("\n");
		if (found == string::npos)
			tokenString = "string";
		else tokenString = "BadNL";
	}
}