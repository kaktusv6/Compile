#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

enum tok_value { ID, INTEGER, HEX, REAL, CHAR, HEXCHAR, DECCHAR, STRING};

/*
Глобальные переменные,
необходимые для работы лексического анализатора
*/

string fname;
int lex_row, lex_col;
tok lex_kind;
string lex_text;
int lex_value;

/*
Вспомогательные глобальные переменные,
описанные в секции реализации модуля
*/

char ch; // Текущий символ
int row, col; // 

/*
Словарь,
сопоставляющий ключевым словам константы типа TLex.
Инициализируется процедурой InitKeywords.
*/
map<string, tok> keywords_map;

void next_ch () {
	lex_text += ch;
	if (!fin.eof()) {
		fin >> ch;
		if (ch != '\n') {
			col++;
		} else {
			row++;
			col = 1;
		}
	} else {
		done();
	}
}

void next_lexem () {
	lex_text = "";
	lex_row = row;
	lex_col = col;
	switch (ch) {
		case 'a'..'z':

		break;
		case '0'..'9':

		break;
		case fin.eof():
			lex_kind = EOF;
		break;

	}
}

void init_keywords () {
	keywords_map['begin'] = BEGIN;
	keywords_map['end'] = END;
}

void init (string fn) {
	init_keywords();
	fname = fn;
	row = 1;
	col = 1;
	next_ch();
	next_lexem();
}

void done () {
	fin.close();
}

string tok_to_string (tok t) {
	switch (t) {
		case tok.ID: return t.toString() + ' ' + lex_text;
		case tok.INTEGER: return t.toString() + ' ' + lex_value;
	}
}