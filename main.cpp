#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stdio.h>
#define DIG "0123456789ABCDEF"

using namespace std;

ofstream fout;
ifstream fin;
stringstream ss;

vector<char> opChar;
vector<char> sepChar;
enum st {LEX, ERR, VAL, NO_WRITE};
map <string, string> strToken;

void addKeyword(string s)
{
	strToken[s] = "keyword";
}
void addOperation(string s)
{
	strToken[s] = "op";
}
void addSeparators(string s)
{
	strToken[s] = "sep";
}
void addOperationInKeywordMap(string s)
{
	strToken[s] = "op";
}
void addSeparator(string s)
{
	strToken[s] = "sep";
}
void initOpChar()
{
	opChar.push_back('+'), opChar.push_back('-'), opChar.push_back('*'), opChar.push_back('^'), opChar.push_back('/'),
		opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('='),
		opChar.push_back('<'), opChar.push_back(':'), opChar.push_back('@'), opChar.push_back('.');
}
void initSepChar()
{
	sepChar.push_back('('), sepChar.push_back(')'),
		sepChar.push_back('['), sepChar.push_back(']'),
		sepChar.push_back(';'), sepChar.push_back(':'),
		sepChar.push_back(',');
}
void initMaps()
{
	addKeyword("begin"), addKeyword("forward"), addKeyword("do"),
		addKeyword("else"), addKeyword("end"), addKeyword("for"), addKeyword("function"),
		addKeyword("if"), addKeyword("array"), addKeyword("of"),
		addKeyword("procedure"), addKeyword("program"), addKeyword("record"), addKeyword("then"),
		addKeyword("to"), addKeyword("type"), addKeyword("var"),
		addKeyword("while"), addKeyword("break"), addKeyword("continue"), addKeyword("downto"),
		addKeyword("exit"), addKeyword("repeat"), addKeyword("until");

	addOperationInKeywordMap("and"), addOperationInKeywordMap("div"), addOperationInKeywordMap("mod"),
		addOperationInKeywordMap("not"), addOperationInKeywordMap("or"), addOperationInKeywordMap("xor");

	addOperation("+"), addOperation("-"), addOperation("*"), addOperation("/"),
		addOperation("^"), addOperation("+="), addOperation("-="), addOperation("*="),
		addOperation("/="), addOperation("<"), addOperation(">"), addOperation("<="),
		addOperation(">="), addOperation("="), addOperation("<>"), addOperation(":="),
		addOperation("@"), addOperation(".");

	addSeparator("("), addSeparator(")"), addSeparator("["), addSeparator("]"), addSeparator(";"),
		addSeparator(":"), addSeparator(".."), addSeparator(",");

	strToken["//"] = "singlelineComment", strToken["(*"] = "multiLineComment";
	initOpChar();
	initSepChar();
}

bool toOperation(char c)
{
	unsigned i = 0;
	while (i < opChar.size() && c != opChar[i]) i++;
	if (i < opChar.size()) return true;
	else return false;
}

bool toSep(char c)
{
	unsigned i = 0;
	while (i < sepChar.size() && c != sepChar[i]) i++;
	if (i < sepChar.size()) return true;
	else return false;
}

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
		if (lexText.length() - 2 == 1 && lexText[1] != '\n')
		{
			tokStr = "char";
			valueStr = lexText[1];
		}
		else if (lexText == "''''")
		{
			tokStr = "char";
			valueStr = "'";
		}
		else
		{
			size_t found = lexText.find("\n");
			if (found == string::npos)
			{
				for (int i = 1; i < lexText.length() - 1; i++) valueStr += lexText[i];
				tokStr = "string";
				for (int i = 0; i < valueStr.length(); i++)
				{
					if (valueStr[i] == '\'') valueStr.erase(i, 1);
					i++;
				}
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
	void parsReal(string s)
	{
		double a;
		a = atof(s.c_str());
		char buf[11];
		sprintf(buf, "%.4E", a);
		buf[8] = buf[9]; buf[9] = buf[10]; buf[10] = 0;
		valueStr = buf;
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
			if (ch == '\n')
			{
				line++;
				col = 0;
			}
			else if (ch == '\t')
			{
				col = (col / 4 + 1) * 4;
			}
			else col++;
		}
		else
		{
			ch = '~';
			endFile = true;
		}
	}
	void done()
	{
		endFile = true;
		fin.close();
	}
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();
	}
public:
	bool endFile;

	Lexer() : line(1), col(0), s(NO_WRITE), endFile(false)
	{
		fin.open("input.txt");
		fout.open("output.txt");

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
			tok.checkOperation(lexText + ch);
			if (tok.tokStr == "BadChar")
			{
				tok.checkOperation(lexText);
				s = LEX;
			}
			else if (tok.tokStr == "op" || tok.tokStr == "sep")
			{
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
			while (ch != '}' && !endFile) nextChar();
			if (endFile)
			{
				lexCol = col + 1;
				lexLine = line;
				tok.tokStr = "BadEOF";
				s = ERR;
			}
			else
			{
				nextChar();
				s = NO_WRITE;
			}
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
					tok.parsReal(lexText);
					tok.tokStr = "real";
					s = VAL;
				}
				else
				{
					lexText.pop_back();
					lexCol--;
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
			while (ch != '\'' && !endFile) nextChar();
			if (endFile)
			{
				lexCol = col + 1;
				tok.tokStr = "BadEOF";
				s = ERR;
			}
			else
			{
				nextChar();
				while (ch == '\'' && !endFile)
				{
					nextChar();
					while (ch != '\'' && !endFile) nextChar();
					if (endFile)
					{
						lexCol = col + 1;
						tok.tokStr = "BadEOF";
						s = ERR;
					}
					nextChar();
				}
				tok.parsString(lexText, lexCol);
				if (tok.tokStr == "BadNL") s = ERR;
				else s = VAL;
			}
		}
		else if (ch == '(')
		{
			nextChar();
			tok.checkOperation(lexText + ch);
			if (tok.tokStr == "multiLineComment")
			{
				while (ch != ')' && !endFile)
				{
					while (ch != '*' && !endFile) nextChar();
					nextChar();
				}

				if (endFile)
				{
					lexCol = col + 1;
					lexLine = line;

					tok.tokStr = "BadEOF";
					s = ERR;
				}
				else
				{
					nextChar();
					s = NO_WRITE;
				}
			}
			else
			{
				tok.tokStr = "sep";
				s = LEX;
			}
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
			if (ch == '~') s = NO_WRITE;
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
	while (!l.endFile && fin.good())
	{
		l.nextLexem();
	}
	return 0;
}