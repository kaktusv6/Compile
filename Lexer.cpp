#include "Lexer.h"
#include "Lexem.h"

#define DIG "0123456789ABCDEF"

using namespace std;

stringstream ss;

//int Atoi(string s){
//	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
//	int i, p = 16, a = 0, digit[256] = { 0 };
//	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
//	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
//	return a;
//}

Lexer::Lexer() : line(1), col(0), endFile(false)
{
	buffer.clear();
	nextChar();
}

void Lexer::parsInteger()
{
	int a = atoi(lexText.c_str());
	TokenValue<int> *t = new TokenValue<int>(lexLine, lexCol, lexText, a);
	t->token = "integer";
	t->printTokenValue();
}

void Lexer::checkKeyword()
{
	Token t(lexLine, lexCol, lexText);
	map<string, string>::iterator i = strToken.find(lexText);
	if (i != strToken.end()) t.token = i->second;
	else t.token = "ident";
	t.printToken();
}

void Lexer::nextChar()
{
	lexText += ch;
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
		done();
		endFile = true;
	}
}

void Lexer::nextLexem()
{
	PassWhiteSpaces();

	lexText.clear();
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
		checkKeyword();
	}
	else if (from0to9(ch))
	{
		while (from0to9(ch)) nextChar();
		parsInteger();
	}
	else if (toSep(ch))
	{
		nextChar();
		Token *t = new Token(lexLine, lexCol, lexText);
		t->token = "sep";
		t->printToken();
		delete t;
	}
	else if (ch == '{')
	{
		while (ch != '}') nextChar();
		nextChar();
		lexText.clear();
	}
	else if (!endFile)
	{
		nextChar();
		done();
		TokenError *t = new TokenError(lexLine, lexCol, "BadChar");
		t->printToken();
		delete t;
	}
	/*else if (from0to9(ch))
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
	}*/
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
	}*/
}

