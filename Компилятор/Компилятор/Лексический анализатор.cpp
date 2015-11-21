#include <iostream>
#include <fstream>
#include <map>
#include <string>

// a - z 97 - 122
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

		writeToken();
	}

	void writeToken()
	{
		/*
		для регулярных выражений запись токена и лексемы неного иначе 
		для регулярных выражений после LexText выводим ???
		*/
		fout /*<< lexLine << '\t' << lineCol << '\t' << '\t'*/ << lexText;
	}

	string tokenToString()
	{

		return "";
	}

	bool fromAToB(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	bool from0to9(char c)
	{
		return (c >= '0' && c <= '9');
	}
};

int main()
{
	Lexer l;
	l.nextLexem();

	system("pause");
	return 0;
}