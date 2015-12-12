#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "Lexem.h"
#include "Token.h"
#include "Lexer.h"

#define DIG "0123456789ABCDEF"

using namespace std;

stringstream ss;

enum st {LEX, ERR, VAL, NO_WRITE};

int Atoi(string s){
	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
	int i, p = 16, a = 0, digit[256] = { 0 };
	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
	return a;
}


int main()
{
	initMaps();
	Lexer l;
	while (l.endFile && !fin.eof())
	{
		l.nextLexem();
	}
	return 0;
}