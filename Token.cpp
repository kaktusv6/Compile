#include <string>
#include <algorithm>

#include "Token.h"

using namespace std;

ofstream fout("output.txt");

void Token::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\n';
}

void TokenValue::printToken()
{
	fout <<lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}

void TokenError::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\n';
}