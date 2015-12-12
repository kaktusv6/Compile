#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

ofstream fout;
ifstream fin;

class Token
{
private:

public:
	int lexLine;
	int lexCol;

	string lexText;
	string token;
	void getToken();
	void clearToken();
};

class TokenValue : public Token
{
public:
	string valueToken;
	virtual void getToken();
	virtual void clearToken();
};

class TokenError : public Token
{
public:
	virtual void getToken();
	virtual void clearToken();
};