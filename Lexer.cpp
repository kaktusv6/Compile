#include "Lexer.h"

#define DIG "0123456789ABCDEF"

static ifstream fin("input.txt");

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
	initialize();
	buffer.clear();
	nextChar();
}

Token* Lexer::parsHex(string text)
{
	if (lexText.length() > 1)
	{
		text.erase(0, 1);
		int valueInt = Atoi(text);
		return new TokenValue<int>(lexLine, lexCol, "hex", text, valueInt);
	}
	else
	{
		return new TokenError(lexLine, col, "NoHex");
	}
}
Token* Lexer::parsInteger(string text)
{
	int integer = atoi(text.c_str());
	return new TokenValue<int>(lexLine, lexCol, "integer", text, integer);
}
Token* Lexer::parsString(string text)
{
	text.erase(0, 1);
	text.erase(value.length()-1, 1);
	
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\'') { text.erase(i, 1); }
	}

	TokenValue<string> *t = new TokenValue<string>(lexLine, lexCol,
													"", text, value);
	if (value.length() == 1) t->setToken("char");
	else t->setToken("string");

	return t;
}

Token* Lexer::creatError(string s)
{
	done();
	return new TokenError(lexLine, col, s);
}

void Lexer::nextChar()
{
	if (ch != EOF)
	{
		if (ch == '\n')
		{
			line++;
			col = 1;
		}
		else if (ch == '\t') col = (col / 4 + 1) * 4;
		else col++;
	}
	lexText += ch;
	ch = fin.get();
	if (ch == EOF)
	{
		ch = '~';
		done();
	}
}
Token*Lexer::nextToken()
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
		if (checkLexem(lexText))
		{
			return new Token(lexLine, lexCol, strToken[lexText], lexText);
		}
		return new Token(lexLine, lexCol, "ident", lexText);
	}
	else if (from0to9(ch))
	{
		while (from0to9(ch)) nextChar();
		return parsInteger(lexText);
	}
	else if (ch == '$')
	{
		nextChar();
		while (isHex(ch)) nextChar();
		return parsHex(lexText);
	}
	else if (isSep(ch))
	{
		nextChar();
		return new Token(lexLine, lexCol, "sep", lexText);
	}
	else if (ch == '{')
	{
		while (ch != '}') nextChar();
		nextChar();
	}
	else if (ch == '\'')
	{
		while (ch == '\'' && !endFile)
		{
			nextChar();
			while (ch != '\'' && !errorString(ch)) nextChar();
			if (endFile) return creatError("BadEOF");
			else if (ch == '\n') return creatError("BadNL");
			else nextChar();
		}
		return parsString(lexText);
	}
	else if (isOperation(ch))
	{
		nextChar();
		if (checkLexem(lexText + ch))
		{
			nextChar();
			return new Token(lexLine, lexCol, strToken[lexText], lexText);
		}
		return new Token(lexLine, lexCol, strToken[lexText], lexText);
	}
	else if (!endFile)
	{
		done();
		return creatError("BadChar");
	}
	return NULL;
	//else if (endFile && ch == '~')
	//{
	//	done();
	//}
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
}

