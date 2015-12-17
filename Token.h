#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

static ifstream fin("input.txt");
static ofstream fout("output.txt");

class Token
{
public:
	int lexLine;
	int lexCol;

	string lexText;
	string token;

	Token(int line, int col, string text);
	virtual void printToken();
};

template<typename Value>
class TokenValue : public Token
{
protected:
	Value valueToken;

public:
	TokenValue(int, int, string);
	
	void setValue(Value v);
	void printTokenValue();
};


class TokenError : public Token
{
public:
	TokenError(int line, int col, string text) :Token(line, col, text) {}
	
	void printToken();
};

template<typename Value>
void TokenValue<Value>::setValue(Value v)
{
	valueToken = v;
}
#endif // TOKEN