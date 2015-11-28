/*ѕроблемы:
	≈сли в конце файла стоит пробел то лексер будет выводить пробел с токеном который был записан до этого момента
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

ofstream fout;
ifstream fin;

const int amountCharOp = 25;

class Lexer
{
private:
	int line = 1;
	int col = 0;
	char ch;
	
	string lexText;
	int lexCol;
	int lexLine;
	
	Token tok;

	vector<char>opCharacter;

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

		nextChar();
	}

	void nextLexem()
	{
		PassWhiteSpaces();

		lexText = "";
		lexCol = col;
		lexLine = line;
		
		if (fromAToB(ch))
		{
			while (fromAToB(ch) || from0to9(ch)) nextChar();
			tok.checkKeyword(lexText);
		}
		else if (toOperation(ch))
		{
			while (toOperation(ch)) nextChar();
			tok.checkOperation(lexText);
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