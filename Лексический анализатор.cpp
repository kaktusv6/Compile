/*ѕроблемы:
	≈сли в конце файла стоит пробел то лексер будет выводить пробел с токеном который был записан до этого момента
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

ofstream fout;
ifstream fin;

const int amountCharOp = 25;

vector<char> opChar;
vector<char> sepChar;
enum st {LEX, ERR, VAL};
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

	addSeparator("("), addSeparator(")"), addSeparator("["), addSeparator("]"), addSeparator(";"), addSeparator(":"), addSeparator(".."), addSeparator(",");
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
	void checkString(string lexText)
	{
		if (lexText.length() == 1)
		{
			tokStr = "char";
		}
		else
		{
			size_t found = lexText.find("\n");
			if (found == string::npos)
				tokStr = "string";
			else tokStr = "BadNL";
		}
	}
	void parsInteger(string s)
	{
		if (s.length() == 1) valueStr = s;
		else
		{
			int i = 0;
			while (s[i] == '0' && i < s.length()) i++;
			while (i < s.length()) valueStr += s[i];
		}
	}
	void parsHex(string s)
	{
		//доделать
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
	int lexCol;
	int lexLine;
	
	Token tok;

	bool fromAtoB(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}
	bool fromAtoF(char c)
	{
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
				col = 1;
			}
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
		endFile = true;
		nextChar();
	}
	void nextLexem()
	{
		PassWhiteSpaces();

		lexText = "";
		lexCol = col;
		lexLine = line;
		
		if (fromAtoB(ch) || ch == '_')
		{
			while (fromAtoB(ch) || from0to9(ch) || ch == '_') nextChar();
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
			}
			else if (tok.tokStr == "op" || tok.tokStr == "sep")
			{
				lexText.pop_back();
				nextChar();
			}
			s = LEX;
		}
		else if (from0to9(ch))
		{
			while (from0to9(ch)) nextChar();
			if (ch == '.')
			{
				nextChar();
				while (from0to9(ch)) nextChar();
				tok.tokStr = "real";
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
			while (fromAtoF(ch) || from0to9(ch)) nextChar();

			s = VAL;
		}
		else if (ch == '\'')
		{
			nextChar();
			while (ch != '\'') nextChar();
			tok.checkString(lexText);
			nextChar();
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
				tok.tokStr = "BadChar";
				s = ERR;
		}
		writeToken();
	}
	void writeToken()
	{
		switch (s)
		{
			case LEX: fout << lexLine << '\t' << lexCol << '\t' + tok.tokStr + '\t' + lexText + '\n'; break;
			case ERR: fout << lexLine << '\t' << lexCol << '\t' + tok.tokStr + '\n'; break;
			case VAL: fout << lexLine << '\t' << lexCol << '\t' + tok.tokStr + '\t' + lexText + '\t' + tok.valueStr + '\n'; break;
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