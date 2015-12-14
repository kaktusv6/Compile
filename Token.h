#pragma once

#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
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

	virtual void printToken();
};

class TokenValue : public Token
{
public:
	int valueToken;
	
	void printToken();
};

class TokenError : public Token
{
public:
	void printToken();
};

#endif // TOKEN_H_INCLUDED