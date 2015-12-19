#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

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
	
	string getToken();

	virtual void printToken();
	void setToken(string);
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
	
	void setValue(Value v);
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

	void setValue(double v);
	void printTokenValue();
};

class TokenError : public Token
{
public:
	TokenError(int line, int col, string text) :Token(line, col, "", text) {}
	
	void printToken();
};

template<class Value>
inline void TokenValue<Value>::setValue(Value v) { valueToken = v; }

template<class Value>
inline void TokenValue<Value>::printToken()
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