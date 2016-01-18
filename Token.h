#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

using namespace std;


class Token
{
protected:
	int lexLine;
	int lexCol;

	string lexText;
	string token;
public:
	static ofstream fout;

	Token(int line, int col, string token, string text);
	
	string getToken()
	{ return this->token; }

	string getLexText() 
	{ return this->lexText; }
	
	string getPosition()
	{
		return to_string(this->lexLine) + " : " + to_string(this->lexCol);
	}
	virtual void printToken();
};

template<class Value>
class TokenValue : public Token
{
protected:
	Value valueToken;

public:
	TokenValue(int line, int col, string text, string token, Value value)
											:Token(line, col, text, token),
											valueToken(value) { }
	
	void printToken();
};

template<>
class TokenValue<double> : public Token
{
protected:
	double valueToken;

public:
	TokenValue(int line, int col, string text, string token, double value)
											:Token(line, col, text, token),
											valueToken(value) {}

	void printToken();
};

template<class Value>
inline void TokenValue<Value>::printToken()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}

inline void TokenValue<double>::printToken()
{
	char buf[245];
	sprintf_s(buf, "%.4E", valueToken);
	
	// remove extra digit in exp
	buf[8] = buf[9]; buf[9] = buf[10]; buf[10] = 0;

	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< buf << '\n';
}

class TokenError : public Token
{
public:
	TokenError(int line, int col, string text) :Token(line, col, "", text) {}
	
	void printToken();
};

#endif // TOKEN