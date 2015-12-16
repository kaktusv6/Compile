#include "Token.h"
using namespace std;

static ofstream fout("output.txt");

Token::Token(int line, int col, string text)
{
	this->lexLine = line;
	this->lexCol = col;
	this->lexText = text;
}

void Token::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\n';
}

void TokenError::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\n';
}

template<typename Value>
TokenValue<Value>::TokenValue(int line, int col, string text)
{
	this->lexLine = line;
	this->lexCol = col;
	this->lexText = text;
}

template<typename Value>
void TokenValue<Value>::printTokenValue()
{
	fout << this->lexLine << '\t'
		<< this->lexCol << '\t'
		<< this->token << '\t'
		<< this->lexText << '\t'
		<< this->valueToken << '\n';
}
