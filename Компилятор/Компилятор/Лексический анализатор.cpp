#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

ofstream fout("output.txt");

enum tok { BEGIN, END, INDENTIFICATOR};

class Lexer
{
private:
	int line;
	int col;
	map<string, tok> keywordsMap;

public:
	Lexer(string name)
	{
		ifstream fin(name);
		
	}

	int addition()
	{
		return line + col;
	}

	void initialization() //инициализация словаря String -> Token
	{

	}

	void 
};

int main()
{
	char ch; // переменная которая считывает код
	int line = 1;
	int col = 1;
	string lexem;

	Lexer m(20, 56);
	cout << m.addition() << endl;
	map<string, tok> keywordsMap;

	while (!fin.eof())
	{
		fin.get(ch);
		if (ch == '\n')
		{
			line++;
			col = 1;
		}
		col++;
		fout << ch;
	}
	system("pause");
	return 0;
}