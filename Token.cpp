#include "Token.h"
#include "Lexer.h"

using namespace std;

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

//TokenError::TokenError(int line, int col, string text)
//{
//	this->lexLine = line;
//	this->lexCol = col;
//	this->lexText = text;
//}
void TokenError::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< lexText << '\n';
}

template<class Value>
TokenValue<Value>::TokenValue(int line, int col, string text)
{
	this->lexLine = line;
	this->lexCol = col;
	this->lexText = text;
}

template<class Value>
inline void TokenValue<Value>::printTokenValue()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}