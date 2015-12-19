#ifndef LEXEM_H
#define LEXEM_H

#include<map>
#include<vector>
#include "Lexer.h"
using namespace std;

Lexer *l = new Lexer();

static void addKeyword(string s)
{
	l->strToken[s] = "keyword";
}
static void addOperation(string s)
{
	l->strToken[s] = "op";
}
static void addSeparators(string s)
{
	strToken[s] = "sep";
}
static void addOperationInKeywordMap(string s)
{
	strToken[s] = "op";
}
static void addSeparator(string s)
{
	strToken[s] = "sep";
}

static void initOpChar()
{
	opChar.push_back('+'), opChar.push_back('-'), opChar.push_back('*'), opChar.push_back('^'), opChar.push_back('/'),
		opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('='),
		opChar.push_back('<'), opChar.push_back(':'), opChar.push_back('@'), opChar.push_back('.');
}
static void initSepChar()
{
	sepChar.push_back('('), sepChar.push_back(')'),
		sepChar.push_back('['), sepChar.push_back(']'),
		sepChar.push_back(';'), sepChar.push_back(':'),
		sepChar.push_back(',');
}
static void initMaps()
{
	addKeyword("begin"), addKeyword("forward"), addKeyword("do"),
		addKeyword("else"), addKeyword("end"), addKeyword("for"), addKeyword("function"),
		addKeyword("if"), addKeyword("array"), addKeyword("of"),
		addKeyword("procedure"), addKeyword("program"), addKeyword("record"), addKeyword("then"),
		addKeyword("to"), addKeyword("type"), addKeyword("var"),
		addKeyword("while"), addKeyword("break"), addKeyword("continue"), addKeyword("downto"),
		addKeyword("exit"), addKeyword("repeat"), addKeyword("until");

	addOperationInKeywordMap("and"), addOperationInKeywordMap("div"), addOperationInKeywordMap("mod"),
		addOperationInKeywordMap("not"), addOperationInKeywordMap("or"), addOperationInKeywordMap("xor");

	addOperation("+"), addOperation("-"), addOperation("*"), addOperation("/"),
		addOperation("^"), addOperation("+="), addOperation("-="), addOperation("*="),
		addOperation("/="), addOperation("<"), addOperation(">"), addOperation("<="),
		addOperation(">="), addOperation("="), addOperation("<>"), addOperation(":="),
		addOperation("@"), addOperation(".");

	addSeparator("("), addSeparator(")"), addSeparator("["), addSeparator("]"), addSeparator(";"),
		addSeparator(":"), addSeparator(".."), addSeparator(",");

	strToken["//"] = "singlelineComment";
	initOpChar();
	initSepChar();
}

#endif // LEXEM