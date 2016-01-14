#include "Token.h"

using namespace std;

ofstream Token::fout("output.txt");

Token::Token(int line, int col, string token, string text)
{
	this->lexLine = line;
	this->lexCol = col;
	this->token = token;
	this->lexText = text;
}

void Token::printToken()
{
	fout <<this->lexLine << '\t'
		<< this->lexCol << '\t'
		<< this->token << '\t'
		<< this->lexText << '\n';
}

void TokenError::printToken()
{
	fout << this->lexLine << '\t'
		<<  this->lexCol << '\t'
		<<  this->lexText << '\n';
}