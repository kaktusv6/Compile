#include "Lexer.h"

#define DIG "0123456789ABCDEF"

int Atoi(string s){
	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
	int i, p = 16, a = 0, digit[256] = { 0 };
	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
	return a;
}

using namespace std;

stringstream ss;

Lexer::Lexer() : line(1), col(0), endFile(false)
{
	buffer.clear();
	nextChar();
}

void Lexer::parsInteger()
{
	int integer = atoi(lexText.c_str());
	TokenValue<int> *t = new TokenValue<int>(lexLine,
		lexCol,
		lexText,
		"integer",
		integer);
	t->printTokenValue();
}
void Lexer::parsHex()
{
	if (lexText.length() > 1)
	{
		TokenValue<int> *t = new TokenValue<int>(lexLine, lexCol, lexText, "hex", 0);
		lexText.erase(0);
		int value = Atoi(lexText);
		t->setValue(value);
	}
	else
	{
		TokenError *e = new TokenError(lexLine, lexCol + 1, "NoHex");
		e->printToken();
	}
}

void Lexer::checkKeyword()
{
	Token t(lexLine, lexCol, "ident", lexText);
	map<string, string>::iterator i = strToken.find(lexText);
	if (i != strToken.end()) t.setToken( i->second );
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
	else if (ch == '$')
	{
		nextChar();
		while (fromAtoF(ch) || from0to9(ch)) nextChar();
		parsHex();
	}
	else if (toSep(ch))
	{
		nextChar();
		Token *t = new Token(lexLine, lexCol, "sep", lexText );
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

