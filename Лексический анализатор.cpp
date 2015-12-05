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
ifstream fin2;

const int amountCharOp = 25;

vector<char> opCharacter;

map <string, string> strToken;
//map <string, string> keywordsToken;
//map <string, string> operationToken;

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

void initOpCharacter()
{
	opCharacter.push_back('+'), opCharacter.push_back('-'), opCharacter.push_back('*'), opCharacter.push_back('^'), opCharacter.push_back('/'), opCharacter.push_back('<'), opCharacter.push_back('>'), opCharacter.push_back('<'), opCharacter.push_back('>'), opCharacter.push_back('='), opCharacter.push_back('<'), opCharacter.push_back(':'), opCharacter.push_back('@'), opCharacter.push_back('.');
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

	initOpCharacter();
}

bool toOperation(char c)
{
	unsigned i = 0;
	while (i < opCharacter.size() && c != opCharacter[i]) i++;
	if (i < opCharacter.size()) return true;
	else return false;
}
//enum Type { OP, INT, SEP };
//string typestr[3] = { "op", "int", "sep" };
class Token
{
private:

public:
	string tokenString;

	void checkKeyword(string lexText)
	{
		map<string, string>::iterator i = keywordsToken.find(lexText);
		if (i != keywordsToken.end()) tokenString = i->second;
		else tokenString = "ident";
	}
	void checkOperation(string lexText)
	{
		map<string, string>::iterator i = operationToken.find(lexText);
		if (i != operationToken.end()) tokenString = i->second;
		else tokenString = "BadChar";
	}
	void checkString(string lexText)
	{
		if (lexText.length() == 1)
		{
			tokenString = "char";
		}
		else
		{
			size_t found = lexText.find("\n");
			if (found == string::npos)
				tokenString = "string";
			else tokenString = "BadNL";
		}
	}
};

class Lexer
{
private:
	int line;
	int col;
	char ch;
	char ch2;
	
	string lexText;
	int lexCol;
	int lexLine;
	
	Token tok;

	bool fromAToB(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
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
		else ch = '\0';
	}
	void done()
	{
		fin.close();
	}
	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t') nextChar();

	}
public:
	Lexer()
	{
		fin.open("input.txt");
		fout.open("output.txt");
		line = 1;
		col = 0;

		nextChar();
	}

	void nextLexem()
	{
		PassWhiteSpaces();

		lexText = "";
		lexCol = col;
		lexLine = line;
		
		if (fromAToB(ch) || ch == '_')
		{
			while (fromAToB(ch) || from0to9(ch) || ch == '_') nextChar();
			tok.checkKeyword(lexText);
		}
		else if (toOperation(ch))
		{
			nextChar();
			lexText += ch;
			tok.checkOperation(lexText);
			if (tok.tokenString == "BadChar")
			{
				lexText.pop_back();
				tok.tokenString = "op";
			}
			else if (tok.tokenString == "op")
			{
				lexText.pop_back();
				nextChar();
			}
		}
		else if (from0to9(ch))
		{
			while (from0to9(ch)) nextChar();
			if (ch == '.')
			{
				nextChar();
				while (from0to9(ch)) nextChar();
				tok.tokenString = "real";
			}
			else tok.tokenString = "integer";
		}
		else if (ch == '\'')
		{
			nextChar();
			while (ch != '\'') nextChar();
			tok.checkString(lexText);
			nextChar();

		}
		writeToken();
	}

	void writeToken()
	{
		fout << lexLine << '\t' << lexCol << '\t' << tok.tokenString + '\t' << lexText << '\n';
	}
};

int main()
{
	initMaps();
	Lexer l;
	while (!fin.eof()){
		l.nextLexem();
	}
	return 0;
}