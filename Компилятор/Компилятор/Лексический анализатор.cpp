#include <iostream>
#include <fstream>
#include <map>
#include <string>

// a - z 97 - 122
// A - Z 
using namespace std;

ofstream fout("output.txt");
ifstream fin("input.txt");

enum tok { BEGIN, END, INDENTIFICATOR, FEOF, SEMICOLON};

class Lexer
{
private:
	int line = 1;
	int col = 1;
	
	map<string, tok> keywordsMap;
	
	string lexText;
	int lexCol;
	int lexLine;
	//if ('a' <= vur <= ')
	char ch;
	tok token;

public:
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
		nextChar();
		PassSpaces();

		lexText = "";
		lexCol = col;
		lexLine = line;

		if ('a' <= ch <= 'z')
		{
			nextChar();
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