#include "Lexer.h"
#include<iostream>
#include "Token.h"
#define DIG "0123456789ABCDEF"

using namespace std;

stringstream ss;

int Atoi(string s){
	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
	int i, p = 16, a = 0, digit[256] = { 0 };
	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
	return a;
}


Lexer::Lexer()
{
	fin.open("input.txt");
	fout.open("output.txt");
	line = 1;
	col = 0;
	s = NO_WRITE;
	endFile = true;
	buffer.clear();
	nextChar();
}

void Lexer::nextLexem()
{
	PassWhiteSpaces();

	lexText = "";
	lexCol = col;
	lexLine = line;

	if (buffer.length() != 0)
	{
		lexText += buffer;
		buffer.clear();
	}

	if (fromAtoZ(ch) || ch == '_')
	{
		while (fromAtoZ(ch) || from0to9(ch) || ch == '_') nextChar();
		tok.checkKeyword(lexText);
		s = LEX;
	}
	else if (toOperation(ch))
	{
		nextChar();
		lexText += ch;
		tok.checkOperation(lexText);
		if (tok.tokStr == "BadChar")
		{
			lexText.pop_back();
			tok.checkOperation(lexText);
			s = LEX;
		}
		else if (tok.tokStr == "op" || tok.tokStr == "sep")
		{
			lexText.pop_back();
			nextChar();
			s = LEX;
		}
		else if (tok.tokStr == "singlelineComment")
		{
			while (ch != '\n' && fin.good()) nextChar();
			s = NO_WRITE;
		}
	}
	else if (ch == '{')
	{
		while (ch != '}') nextChar();
		nextChar();
		s = NO_WRITE;
	}
	else if (from0to9(ch))
	{
		while (from0to9(ch)) nextChar();
		if (ch == '.')
		{
			buffer += ch;
			nextChar();
			if (from0to9(ch))
			{
				buffer.clear();
				while (from0to9(ch)) nextChar();
				tok.tokStr = "real";
				tok.valueStr = lexText;
				s = VAL;
			}
			else
			{
				lexText.pop_back();
				tok.tokStr = "integer";
				tok.parsInteger(lexText);
				s = VAL;
			}
		}
		else
		{
			tok.tokStr = "integer";
			tok.parsInteger(lexText);
		}
		s = VAL;
	}
	else if (ch == '$')
	{
		nextChar();
		while (fromAtoF(ch) || from0to9(ch)) nextChar();
		if (lexText.length() > 1)
		{
			tok.parsHex(lexText);
			tok.tokStr = "hex";
			s = VAL;
		}
		else
		{
			lexCol++;
			tok.tokStr = "NoHex";
			s = ERR;
		}

	}
	else if (ch == '\'')
	{
		nextChar();
		while (ch != '\'') nextChar();
		nextChar();
		tok.parsString(lexText, lexCol);
		if (tok.tokStr == "BadNL") s = ERR;
		else s = VAL;
	}
	else if (toSep(ch))
	{
		nextChar();
		tok.tokStr = "sep";
		s = LEX;
	}
	else
	{
		done();
		if (ch == -1) s = NO_WRITE;
		else
		{
			tok.tokStr = "BadChar";
			s = ERR;
		}
	}
}