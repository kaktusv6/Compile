#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Token.h"

// a - z 97 - 122
using namespace std;

ofstream fout;
ifstream fin;

class Lexer
{
private:
	int line = 1;
	int col = 1;
	char ch;
	
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

public:
	Lexer()//конструктор класса
	{
		fin.open("input.txt");
		fout.open("output.txt");

		nextChar();
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
		else ch = '№';
	}

	void done()
	{
		fin.close();
	}

	void PassWhiteSpaces()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t' ) nextChar();
		
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
			
		}

		/*if (from0to9(ch))
		{
			while (from0to9) nextChar();
		}*/
		writeToken();
	}

	void writeToken()
	{
		/*
		для регулярных выражений запись токена и лексемы неного иначе 
		для регулярных выражений после LexText выводим ???
		*/
		fout << lexLine << '\t' << lexCol << '\t' << tok.tokenToString() << '\t' << lexText << '\n';
	}

	string tokenToString()
	{

		return "";
	}
};

int main()
{
	Lexer l;
	l.nextLexem();

	system("pause");
	return 0;
}