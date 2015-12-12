#include "Token.h"
#include <string>
#include <algorithm>

using namespace std;

void Token::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\n';
}
void Token::clearToken()
{
	lexText.clear();
	token.clear();
}

void TokenValue::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}
void TokenValue::clearToken()
{
	lexText.clear();
	token.clear();
}

void TokenError::getToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\n';
}
void TokenError::clearToken()
{
	lexText.clear();
	token.clear();
}