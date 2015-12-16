#ifndef TOKEN
#define TOKEN

#include<iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

static ifstream fin("input.txt");


class Token
{
public:
	int lexLine;
	int lexCol;

	string lexText;
	string token;

	Token(int line, int col, string text);
	virtual void printToken();
	//~Token() { cout << "Destruktor" << '\n'; }
};

template<typename Value>
class TokenValue : public Token
{
public:
	Value valueToken;
	
	TokenValue(int line, int col, string text);
	void printTokenValue();
};

class TokenError : public Token
{
public:
	void printToken();
};
#endif // TOKEN