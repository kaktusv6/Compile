#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cctype>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

enum tokValue { ID, INTEGER, HEX, REAL, CHAR, HEXCHAR, DECCHAR, STRING, BEGIN, END };

/*
���������� ����������,
����������� ��� ������ ������������ �����������
*/

string fname;
int lexRow, lexCol;
tokValue lexKind;
string lexText;
int lexValue;

/*
��������������� ���������� ����������,
��������� � ������ ���������� ������
*/

char ch; // ������� ������
int row, col; // 

/*
�������,
�������������� �������� ������ ��������� ���� TLex.
���������������� ���������� InitKeywords.
*/
map<string, tokValue> keywordsMap;

void nextCh() {
	lexText += ch;
	if (!fin.eof()) {
		fin >> ch;
		if (ch != '\n') {
			col++;
		}
		else {
			row++;
			col = 1;
		}
	}
	else {
		done();
	}
}

void nextLexem()
{
	lexText = "";
	lexRow = row;
	lexCol = col;
	switch (ch) {
	case tolower(ch) == ch:

		break;
	case '0':'9';

		break;
	case fin.eof():
		lexKind = EOF;
		break;

	}
}

void initKeywords()
{
	keywordsMap["begin"] = BEGIN;
	keywordsMap["end"] = END;
}

void init(string fn)
{
	initKeywords();
	fname = fn;
	row = 1;
	col = 1;
	nextCh();
	nextLexem();
}

void done()
{
	fin.close();
}

string tokValueToString(tokValue t)
{
	switch (t) {
	case ID: return t.toString() + ' ' + lexText; // �������� ������� �������������� ������ � string
	case INTEGER: return  + ' ' + lexValue;
	}
}