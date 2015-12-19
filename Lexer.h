#ifndef LEXER_H
#define LEXER_H
#include <sstream>
#include "Token.h"
#include "Lexem.h"

using namespace std;

class Lexer
{
private:
	int line;
	int col;
	int lexLine;
	int lexCol;

	char ch;
	
	string lexText;
	string value;
	string buffer;

	bool endFile;

	/*void checkOperation(string lexText)
	{
	map<string, string>::iterator i = strToken.find(lexText);
	if (i != strToken.end()) tokStr = i->second;
	else tokStr = "BadChar";
	}*/

	bool fromAtoZ(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}
	bool from0to9(char c)
	{
		return (c >= '0' && c <= '9');
	}
	bool errorString(char c)
	{
		return ch == '\n' || endFile;
	}
	bool isHex(char c)
	{
		return c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f' || c >= '0' && c <= '9';
	}
	bool isOperation(char c)
	{
		unsigned i = 0;
		while (i < opChar.size() && c != opChar[i]) i++;
		if (i < opChar.size()) return true;
		else return false;
	}
	bool isSep(char c)
	{
		unsigned i = 0;
		while (i < sepChar.size() && c != sepChar[i]) i++;
		if (i < sepChar.size()) return true;
		else return false;
	}
	void checkKeyword();

	void nextChar();
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();
	}

	Token* parsHex(string);
	Token* parsInteger();
	Token* parsString();

	void done()
	{
		endFile = true;
		fin.close();
	}
	Token* creatError(string);
public:
	Lexer();

	Token* nextToken();
	bool getEndFile() { return endFile; }
};

#endif // LEXER