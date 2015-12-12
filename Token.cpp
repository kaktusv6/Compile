#include "Token.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Token::Token()
{

}

void Token::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\n';
}

void TokenValue::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}

void TokenError::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\n';
}