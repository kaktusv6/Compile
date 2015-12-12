#include "Lexer.h"
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
	line = 1;
	col = 0;
	endFile = true;
	buffer.clear();
	tok = &token;
	nextChar();
}

void Lexer::checkKeyword(Token *t)
{
	map<string, string>::iterator i = strToken.find(t->lexText);
	if (i != strToken.end()) t->token = i->second;
	else t->token = "ident";
	t->getToken();
}
void Lexer::nextChar()
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
void Lexer::nextLexem()
{
	PassWhiteSpaces();

	tok->lexText = "";
	tok->lexCol = col;
	tok->lexLine = line;

	if (buffer.length() != 0)
	{
		tok->lexText += buffer;
		buffer.clear();
	}

	if (fromAtoZ(ch) || ch == '_')
	{
		while (fromAtoZ(ch) || from0to9(ch) || ch == '_') nextChar();
		checkKeyword(tok);
	}
	/*else if (toOperation(ch))
	{
		nextChar();
		tok->lexText += ch;
		checkOperation(tok->lexText);
		if ( == "BadChar")
		{
			tok->lexText.pop_back();
			checkOperation(tok->lexText);
			s = LEX;
		}
		else if (tr == "op" || tr == "sep")
		{
			tok->lexText.pop_back();
			nextChar();
			s = LEX;
		}
		else if (tr == "singlelineComment")
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
				tr = "real";
				valueStr = tok->lexText;
				s = VAL;
			}
			else
			{
				tok->lexText.pop_back();
				tr = "integer";
				parsInteger(tok->lexText);
				s = VAL;
			}
		}
		else
		{
			tr = "integer";
			parsInteger(tok->lexText);
		}
		s = VAL;
	}
	else if (ch == '$')
	{
		nextChar();
		while (fromAtoF(ch) || from0to9(ch)) nextChar();
		if (tok->lexText.length() > 1)
		{
			parsHex(tok->lexText);
			tr = "hex";
			s = VAL;
		}
		else
		{
			lexCol++;
			tr = "NoHex";
			s = ERR;
		}

	}
	else if (ch == '\'')
	{
		nextChar();
		while (ch != '\'') nextChar();
		nextChar();
		parsString(tok->lexText, lexCol);
		if (tr == "BadNL") s = ERR;
		else s = VAL;
	}
	else if (toSep(ch))
	{
		nextChar();
		tr = "sep";
		s = LEX;
	}
	else
	{
		done();
		if (ch == -1) s = NO_WRITE;
		else
		{
			tr = "BadChar";
			s = ERR;
		}
	}*/
}