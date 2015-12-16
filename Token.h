#pragma once

#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include<iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

static ifstream fin("input.txt");


class Token
{
private:

public:
	int lexLine;
	int lexCol;

	string lexText;
	string token;

	Token(int, int, string);
	virtual void printToken();
	//~Token() { cout << "Destruktor" << '\n'; }
};

template<typename T>
class TokenValue : public Token
{
public:
	T valueToken;
	
	TokenValue() : Token() { };
	void printTokenValue();
	bool TrueFalse();
};

class TokenError : public Token
{

public:
	void printToken();
};

#endif // TOKEN_H_INCLUDED