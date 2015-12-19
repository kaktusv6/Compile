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
	initMaps();
	buffer.clear();
	nextChar();
}

void Lexer::checkKeyword()
{
	Token *t = new Token(lexLine, lexCol, "ident", lexText);
	map<string, string>::iterator i = strToken.find(lexText);
	if (i != strToken.end()) t->setToken(i->second);
	t->printToken();
	delete t;
}

Token* Lexer::parsHex(string text)
{
	if (lexText.length() > 1)
	{
		int valueInt = Atoi(text);
		TokenValue<int> *t = new TokenValue<int>(lexLine, lexCol,
											"hex", text, valueInt);
		return t;
	}
	else
	{
		TokenError *error = new TokenError(lexLine, col, "NoHex");
	}
}
Token* Lexer::parsInteger(string text)
{
	int integer = atoi(text.c_str());
	TokenValue<int> *t = new TokenValue<int>(lexLine,
		lexCol,
		text,
		"integer",
		integer);
	return t;
}
Token* Lexer::parsString(string text)
{
	value = text;

	value.erase(0, 1);
	value.erase(value.length()-1, 1);
	
	for (int i = 0; i < value.length(); i++)
	{
		if (value[i] == '\'')
		{
			value.erase(i, 1);
			i++;
		}
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
	TokenError *t = new TokenError(lexLine, col, s);
	return t;
}

void Lexer::nextChar()
{
	if (ch != EOF)
	{
		if (ch == '\n')
		{
			line++;
			col = 0;
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
		checkKeyword();
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
		Token *t = new Token(lexLine, lexCol, "sep", lexText );
		t->printToken();
		delete t;
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
		tok->lexText += ch;
		checkOperation(tok->lexText);
		if (== "BadChar")
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

