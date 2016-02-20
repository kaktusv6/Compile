#ifndef LEXER_H
#define LEXER_H
#include <sstream>
#include "Lexem.h"
#include "Token.h"

using namespace std;

class Lexer
{
private:
	int line;
	int col;
	int lexLine;
	int lexCol;

	bool endFile;

	char ch;
	
	string lexText;
	string value;

	Token* buffer;

	bool isExponent(char c)
	{
		return c == 'e' || c == 'E';
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
	bool isCodeChar(int i)
	{
		return i >= 0 && i <= 127;
	}
	bool checkLexem(string text)
	{
		return (strToken.find(text) != strToken.end() ? true : false);
	}

	void nextChar();
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();
	}
	void done()
	{
		endFile = true;
	}
	
	string parsString(string);

	Token* creatError(string);
public:
	Lexer();

	void setBuffer(Token * t) { buffer = t; }
	
	Token* nextToken();
	Token* getBuffer() { return buffer; }

	bool getEndFile() { return endFile; }
};

//#include"Lexer.cpp"
#endif // LEXER