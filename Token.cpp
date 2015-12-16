#include "Token.h"
using namespace std;

ofstream fout("output.txt");

Token::Token(int line, int col, string text): lexLine(line),
												lexCol(col),
												lexText(text)
												{ }
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

template<typename T>
bool TokenValue<T>::TrueFalse()
{
	cout << true << endl;
	system("pause");
}
template<typename T>
void TokenValue<T>::printTokenValue()
{
	fout<< lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}
