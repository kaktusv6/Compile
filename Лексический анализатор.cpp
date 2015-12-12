#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "Lexem.h"
#define DIG "0123456789ABCDEF"

using namespace std;

ofstream fout;
ifstream fin;
stringstream ss;


enum st {LEX, ERR, VAL, NO_WRITE};



int Atoi(string s){
	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
	int i, p = 16, a = 0, digit[256] = { 0 };
	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
	return a;
}

class Token
{
private:

public:
	string tokStr;
	string valueStr;

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
				col = found+1;
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
			while (s[i] == '0' && i < n-1) i++;
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

	
};

class Lexer
{
private:
	int line;
	int col;
	char ch;
	char ch2;
	st s;

	string lexText;
	string buffer;
	int lexCol;
	int lexLine;
	
	Token tok;

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
		lexText += ch;
		if ((ch = fin.get()) != EOF)
		{
			//fin.get(ch);
			if (ch == '\n')
			{
				line++;
				col = 0;
			}
			//else if (ch == '\t')
			//{
			//	col += (8 - col % 9);
			//}
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
	bool endFile;

	Lexer()
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
	void nextLexem()
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
		writeToken();
	}
	void writeToken()
	{
		switch (s)
		{
			case LEX: fout << lexLine << '\t'
				<< lexCol << '\t' 
				<< tok.tokStr << '\t'
				<< lexText + '\n';
				break;
			case ERR:
				fout << lexLine << '\t' 
					<< lexCol << '\t'
					<< tok.tokStr;
				done();
				break;
			case VAL:
				fout << lexLine << '\t'
					<< lexCol << '\t'
					<< tok.tokStr << '\t'
					<< lexText << '\t'
					<< tok.valueStr << '\n';
				tok.valueStr = "";
				break;
			case NO_WRITE:break;
		}
	}

};

int main()
{
	initMaps();
	Lexer l;
	while (l.endFile && !fin.eof())
	{
		l.nextLexem();
	}
	return 0;
}