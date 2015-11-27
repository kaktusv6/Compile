#include "Token.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Token::Token()
{
	keywordsToken.insert(pair<string, string>("begin", "keyword"));
	keywordsToken.insert(pair<string, string>("forward", "keyword"));
	keywordsToken.insert(pair<string, string>("do", "keyword"));
	keywordsToken.insert(pair<string, string>("else", "keyword"));
	keywordsToken.insert(pair<string, string>("end", "keyword"));
	keywordsToken.insert(pair<string, string>("for", "keyword"));
	keywordsToken.insert(pair<string, string>("function", "keyword"));
	keywordsToken.insert(pair<string, string>("if", "keyword"));
	keywordsToken.insert(pair<string, string>("array", "keyword"));
	keywordsToken.insert(pair<string, string>("of", "keyword"));
	keywordsToken.insert(pair<string, string>("procedure", "keyword"));
	keywordsToken.insert(pair<string, string>("program", "keyword"));
	keywordsToken.insert(pair<string, string>("record", "keyword"));
	keywordsToken.insert(pair<string, string>("then", "keyword"));
	keywordsToken.insert(pair<string, string>("to", "keyword"));
	keywordsToken.insert(pair<string, string>("type", "keyword"));
	keywordsToken.insert(pair<string, string>("var", "keyword"));
	keywordsToken.insert(pair<string, string>("while", "keyword"));
	keywordsToken.insert(pair<string, string>("break", "keyword"));
	keywordsToken.insert(pair<string, string>("continue", "keyword"));
	keywordsToken.insert(pair<string, string>("downto", "keyword"));
	keywordsToken.insert(pair<string, string>("exit", "keyword"));
	keywordsToken.insert(pair<string, string>("repeat", "keyword"));
	keywordsToken.insert(pair<string, string>("until", "keyword"));

	keywordsToken.insert(pair<string, string>("and", "op"));
	keywordsToken.insert(pair<string, string>("div", "op"));
	keywordsToken.insert(pair<string, string>("mod", "op"));
	keywordsToken.insert(pair<string, string>("not", "op"));
	keywordsToken.insert(pair<string, string>("or", "op"));
	keywordsToken.insert(pair<string, string>("xor", "op"));
	
	operationToken.insert(pair<string, string>("+", "op"));
	operationToken.insert(pair<string, string>("-", "op"));
	operationToken.insert(pair<string, string>("*", "op"));
	operationToken.insert(pair<string, string>("/", "op"));
	operationToken.insert(pair<string, string>("^", "op"));
	operationToken.insert(pair<string, string>("+=", "op"));
	operationToken.insert(pair<string, string>("-=", "op"));
	operationToken.insert(pair<string, string>("*=", "op"));
	operationToken.insert(pair<string, string>("/=", "op"));
	operationToken.insert(pair<string, string>("<", "op"));
	operationToken.insert(pair<string, string>(">", "op"));
	operationToken.insert(pair<string, string>("<=", "op"));
	operationToken.insert(pair<string, string>(">=", "op"));
	operationToken.insert(pair<string, string>("=", "op"));
	operationToken.insert(pair<string, string>("<>", "op"));
	operationToken.insert(pair<string, string>(":=", "op"));
	operationToken.insert(pair<string, string>("@", "op"));
	operationToken.insert(pair<string, string>(".", "op"));


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