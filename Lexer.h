#pragma once
#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
#include <sstream>
#include "Token.h"
#include "Lexem.h"

using namespace std;

class Lexer
{
private:
	int line;
	int col;

	char ch;

	string buffer;

	Token tok;
	TokenError tokError;

	/*void checkOperation(string lexText)
	{
		map<string, string>::iterator i = strToken.find(lexText);
		if (i != strToken.end()) tokStr = i->second;
		else tokStr = "BadChar";
	}
	void parsString(string lexText, int &col)
	{
		if (lexText.length() == 1)
		{
			tokStr = "char";
			valueStr = lexText[0];
		}
		else
		{
			size_t found = lexText.find("\n");
			if (found == string::npos)
			{
				for (int i = 1; i < lexText.length() - 1; i++) valueStr += lexText[i];
				tokStr = "string";
			}
			else
			{
				col = found + 1;
				tokStr = "BadNL";
			}
		}
	}*/
	void parsInteger(TokenValue<int> t);
	/*
	void parsHex(string s)
	{
		int val = 0;
		val = Atoi(s);
		ss << val;
		valueStr = ss.str();
	}*/

	bool fromAtoZ(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}
	bool fromAtoF(char c)
	{
		c = toupper(c);
		return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
	}
	bool from0to9(char c)
	{
		return (c >= '0' && c <= '9');
	}
	bool toOperation(char c)
	{
		unsigned i = 0;
		while (i < opChar.size() && c != opChar[i]) i++;
		if (i < opChar.size()) return true;
		else return false;
	}
	bool toSep(char c)
	{
		unsigned i = 0;
		while (i < sepChar.size() && c != sepChar[i]) i++;
		if (i < sepChar.size()) return true;
		else return false;
	}

	void checkKeyword(Token t);
	void nextChar();
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();
	}

	void done()
	{
		endFile = false;
		fin.close();
	}
public:
	bool endFile;

	Lexer();
	void nextLexem();
};

#endif // LEXER_H_INCLUDED