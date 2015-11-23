/*��������:
	��������� ��������� ������ 2 ���� �� �� eof
	���� � ����� ����� ����� ������ �� ������ ������� ��� ��� keyword
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
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

	char *opCharacter = new char[amountCharOp];

	bool fromAToB(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	bool from0to9(char c)
	{
		return (c >= '0' && c <= '9');
	}

	bool toOperation(char c)
	{
		int i = 0;
		while (c != opCharacter[i]) i++;
		if (i < strlen(opCharacter)) return true;
		else return false;
	}
	void nextChar()
	{
		lexText += ch;
		if (!fin.eof())
		{
			fin.get(ch);
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

		opCharacter = "admnox+-*/^+-*/<><>=<:@.";
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
		else
		{
			while (ch != ' ') nextChar();
			tok.checkOperation(lexText);
		}
		writeToken();
	}

	void writeToken()
	{
		fout << lexLine << '\t' << lexCol << '\t' << tok.tokenString << '\t' << lexText << '\n';
	}
};

int main()
{
	Lexer l;
	while (!fin.eof()) l.nextLexem();
	return 0;
}