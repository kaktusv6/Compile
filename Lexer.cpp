#include "Lexer.h"
#include<iostream>
#include "Token.h"
#define DIG "0123456789ABCDEF"

using namespace std;

stringstream ss;

int Atoi(string s){
	for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
	int i, p = 16, a = 0, digit[256] = { 0 };
	for (i = 0; DIG[i]; i++) digit[DIG[i]] = i;
	for (i = 1; i < s.length(); i++) a = a * p + digit[s[i]];
	return a;
}


Lexer::Lexer()
{
	fin.open("input.txt");
	fout.open("output.txt");
	line = 1;
	col = 0;
	s = NO_WRITE;
	endFile = true;
	buffer.clear();
	nextChar();
}

