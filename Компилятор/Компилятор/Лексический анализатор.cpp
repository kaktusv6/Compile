#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

ofstream fout("output.txt");
ifstream fin("input.txt");

enum tok { BEGIN, END, INDENTIFICATOR};

class Lexer
{
private:
	int line = 1;
	int col = 1;
	
	map<string, tok> keywordsMap;
	
	string LexText;
	char ch;

public:
	void nextChar()
	{
		LexText += ch;
		if (!fin.eof())
		{
			fin.get(ch);
			if (ch == '\n')
			{
				line++;
				col++;
			}
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
			fin.get(ch);
			col++;
		}
	}
};

int main()
{

	system("pause");
	return 0;
}