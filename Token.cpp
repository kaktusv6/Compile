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

/*TokenValue<T>::TokenValue(int _lexLine, int _lexCol, string _token, string _lexText)
{
	lexLine = _lexLine;
	lexcol = _lexcol;
	token = _token;
	lexText = _lexText;
}*/

template<typename T>
void TokenValue<typename T>::printToken()
{
	fout << lexLine << '\t'
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