#include <iostream>
#include <fstream>
#include <map>
#include <string>

// a - z 97 - 122
// A - Z 
using namespace std;

ofstream fout;
ifstream fin;

enum tok { ID, BEGIN, END, IDENT, FEOF, SEMICOLON};

class Lexer
{
private:
	int line = 1;
	int col = 1;
	
	map<string, tok> keywordsMap;
	
	string lexText;
	int lexCol;
	int lexLine;
	char ch;
	tok token;

public:
	Lexer()
	{
		keywordsMap["begin"] = BEGIN;
		keywordsMap["end"] = END;
		
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
		else done();
	}

	void done()
	{
		fin.close();
	}

	void PassSpaces()
	{
		while (ch == ' ')
		{
			nextChar();
		}
	}
	void nextLexem()
	{
		PassSpaces();

		lexText = "";
		lexCol = col;
		lexLine = line;

		if ('a' <= ch <= 'z')
		{
			while ('a' <= ch <= 'z' && !fin.eof())
			{
				nextChar();
			}
		}


	}

	void writeToken()
	{
		/*
		для регулярных выражений запись токена и лексемы неного иначе 
		для регулярных выражений после LexText выводим ???
		*/
		fout << line << '\t' << col << '\t' << token << '\t' << lexText;
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