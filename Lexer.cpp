#include "Lexer.h"

static ifstream fin("input.txt");

using namespace std;

Lexer::Lexer() : line(1), col(0), endFile(false), buffer(NULL)
{
	initialize();
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
		else if (ch == '\t') col = (((col - 1) / 4) + 1) * 4 + 1;
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

	if (buffer != NULL)
	{
		Token* t = buffer;
		buffer = NULL;
		return t;
	}

	if (isalpha(ch) || ch == '_')
	{
		while (isalnum(ch) || ch == '_') nextChar();
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
			while (ch != '\n')
			{
				nextChar();
				if (endFile) break;
			}
			return NULL;
		}
		if (checkLexem(lexText + ch)) { nextChar(); }
		return new Token(lexLine, lexCol, strToken[lexText], lexText);
	}
	else if (isdigit(ch))
	{
		while (isdigit(ch)) nextChar();

		if (ch == '.') nextChar();
		else if (isExponent(ch))
		{
			nextChar();
			bool chIsOp = ch == '+' || ch == '-';
			if (chIsOp)
			{
				nextChar();
				if (!isdigit(ch)) return creatError("NoExp");
				while (isdigit(ch)) nextChar();
				return new TokenValue<double>(lexLine, lexCol, "real",
										lexText, atof(lexText.c_str()));
			}
			if (!isdigit(ch)) return creatError("NoExp");
			while (isdigit(ch)) nextChar();
			return new TokenValue<double>(lexLine, lexCol, "real",
				lexText, atof(lexText.c_str()));
		}
		else 
		{
			return new TokenValue<int>(lexLine, lexCol, "integer",
										lexText, atoi(lexText.c_str()));
		}
		if (isdigit(ch))
		{
			while (isdigit(ch)) nextChar();
			if (isExponent(ch))
			{
				nextChar();
				bool chIsOp = ch == '+' || ch == '-';
				if (chIsOp)
				{
					nextChar();
					if (!isdigit(ch)) return creatError("NoExp");
					while (isdigit(ch)) nextChar();
					return new TokenValue<double>(lexLine, lexCol, "real",
							lexText, atof(lexText.c_str()));
				}
				if (!isdigit(ch)) return creatError("NoFract");
				while (isdigit(ch)) nextChar();
				return new TokenValue<double>(lexLine, lexCol, "real",
							lexText, atof(lexText.c_str()));
			}
			else
			{
				return new TokenValue<double>(lexLine, lexCol, "real",
										lexText, atof(lexText.c_str()));
			}
		}
		if (ch == '.')
		{
			buffer = new Token(line, col - 1, "sep", "..");
			nextChar();
			lexText.pop_back(), lexText.pop_back();
			return new TokenValue<int>(lexLine, lexCol, "integer",
									lexText, atoi(lexText.c_str()));
		}

		return creatError("NoFract");
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
					return new TokenValue<char>(lexLine, lexCol, "char",
													lexText, (char)value);
				}
				return creatError("BadCC");
			}
			return creatError("NoHex");
		}
		while (isdigit(ch)) nextChar();
		if (lexText.length() != 1)
		{
			int value = atoi(lexText.substr(1).c_str());
			if (isCodeChar(value))
			{
				return new TokenValue<char>(lexLine, lexCol, "char",
												lexText, (char)value);
			}
			return creatError("BadCC");
		}
		return creatError("NoCC");
	}
	else if (isSep(ch))
	{
		nextChar();
		if (lexText + ch == "(*")
		{
			while (ch != ')')
			{
				while (ch != '*')
				{
					nextChar();
					if (endFile) return creatError("BadEOF");
				}
				nextChar();
				if (endFile) return creatError("BadEOF");
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
		if (value.length() != 1)
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