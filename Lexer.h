#pragma once
#include "Token.h"

using namespace std;
enum st { LEX, ERR, VAL, NO_WRITE };

class Lexer
{
private:
	int line;
	int col;

	char ch;

	st s;

	string buffer;

	Token *tok;
	Token token;
	TokenValue tokenValue;
	TokenError tokenError;

	bool endFile;

	void checkKeyword(string lexText)
	{
		map<string, string>::iterator i = strToken.find(lexText);
		if (i != strToken.end()) tokStr = i->second;
		else tokStr = "ident";
	}
	void checkOperation(string lexText)
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
	}
	void parsInteger(string s)
	{
		int n = s.length();
		if (n == 1) valueStr = s;
		else
		{
			int i = 0;
			while (s[i] == '0' && i < n - 1) i++;
			while (i < n)
			{
				valueStr += s[i];
				i++;
			}
		}
	}
	void parsHex(string s)
	{
		int val = 0;
		val = Atoi(s);
		ss << val;
		valueStr = ss.str();
	}

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
	void nextChar()
	{
		tok->lexText += ch;
		if ((ch = fin.get()) != EOF)
		{
			if (ch == '\n')
			{
				line++;
				col = 0;
			}
			else col++;
		}
		else
		{
			endFile = false;
		}
	}
	void done()
	{
		endFile = false;
		fin.close();
	}
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();
	}

public:
	Lexer();
	void nextLexem();
};