#include "Lexer.h"

static ifstream fin("input.txt");

using namespace std;

Lexer::Lexer() : line(1), col(0), endFile(false)
{
	initialize();
	buffer.clear();
	nextChar();
}

string Lexer::parsString(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (text.at(i) == '\'') { text.erase(i, 1); }
	}
	return text;
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
	else if (isOperation(ch))
	{
		nextChar();
		if (lexText + ch == "//")
		{
			while (ch != '\n') { nextChar(); }
			return NULL;
		}
		if (checkLexem(lexText + ch)) { nextChar(); }
		return new Token(lexLine, lexCol, strToken[lexText], lexText);
	}
	else if (from0to9(ch))
	{
		while (from0to9(ch)) nextChar();
		return new TokenValue<int>(lexLine, lexCol, "integer",
									lexText, atoi(lexText.c_str()));
	}
	else if (ch == '$')
	{
		nextChar();
		while (isHex(ch)) nextChar();
		if (lexText.length() > 1) 
		{
			int value = stoll(lexText.substr(1), nullptr, 16);
			return new TokenValue<int>(lexLine, lexCol, "hex", lexText, value);
		}
		return creatError("NoHex");
	}
	else if (ch == '#')
	{
		nextChar();
		if (ch == '$')
		{
			nextChar();
			while (isHex(ch)) nextChar();
			if (lexText.length() > 2)
			{
				int value = stoll(lexText.substr(2), nullptr, 16);
				if (isCodeChar(value))
				{
					return new TokenValue<char>(lexLine, lexCol, "char", lexText, (char)value);
				}
				return creatError("NoCC");
			}
			return creatError("NoHex");
		}
		while (from0to9(ch)) nextChar();
		if (lexText.length() > 1)
		{
			int value = atoi(lexText.substr(1).c_str());
			if (isCodeChar(value))
			{
				return new TokenValue<char>(lexLine, lexCol, "char", lexText, (char)value);
			}
		}
		return creatError("NoCC");
	}
	else if (isSep(ch))
	{
		nextChar();
		if (ch == '*')
		{
			nextChar();
			while (ch != ')')
			{
				while (ch != '*')
				{
					nextChar();
				}
				nextChar();
			}
			nextChar();
			return NULL;
		}
		return new Token(lexLine, lexCol, "sep", lexText);
	}
	else if (ch == '{')
	{
		while (ch != '}')
		{
			nextChar();
			if (endFile) { return creatError("BadEOF"); }
		}
		nextChar();
		return NULL;
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
		string value = parsString(lexText.substr(1, lexText.length() - 2));
		if (value.length() > 1)
			return new TokenValue<string>(lexLine, lexCol, "string", lexText, value);

		return new TokenValue<string>(lexLine, lexCol, "char", lexText, value);
	}
	else if (!endFile)
	{
		done();
		return creatError("BadChar");
	}
	return NULL;
}