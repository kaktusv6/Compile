#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
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
private:
	Value valueToken;

public:
	TokenValue(int line, int col, string text, Value value) :Token(line, col, text) : valueToken(value) { }
	
	void setValue(Value v);
	void printTokenValue();
};

template<>
class TokenValue<double> : public Token
{
private:
	double valueToken;

public:
	TokenValue(int line, int col, string text, double value) :Token(line, col, text), valueToken(value) {}

	void setValue(double v);
	void printTokenValue();
};

class TokenError : public Token
{
public:
	TokenError(int line, int col, string text) :Token(line, col, text) {}
	
	void printToken();
};

template<typename Value>
inline void TokenValue<Value>::setValue(Value v)
{
	valueToken = v;
}

template<class Value>
inline void TokenValue<Value>::printTokenValue()
{
	fout << lexLine << '\t'
		<< lexCol << '\t'
		<< token << '\t'
		<< lexText << '\t'
		<< valueToken << '\n';
}

//template<>
//inline void TokenValue<double>::printTokenValue()
//{
//	fout << lexLine << '\t'
//		<< lexCol << '\t'
//		<< token << '\t'
//		<< lexText << '\t'
//		<< valueToken << '\n';
//}
#endif // TOKEN