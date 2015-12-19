#ifndef LEXEM_H
#define LEXEM_H

#include<map>
#include<vector>

using namespace std;

static map <string, string> strToken;

static vector<char> opChar;
static vector<char> sepChar;

static void addKeyword(string s)
{
	strToken[s] = "keyword";
}
static void addOperation(string s)
{
	strToken[s] = "op";
}
static void addSeparators(string s)
{
	strToken[s] = "sep";
}
static void addSeparator(string s)
{
	strToken[s] = "sep";
}
static void addOpChar(char c)
{
	opChar.push_back(c);
}
static void addSepChar(char c)
{
	sepChar.push_back(c);
}

static void initialize()
{
	addKeyword("begin"), addKeyword("forward"), addKeyword("do"),
		addKeyword("else"), addKeyword("end"), addKeyword("for"), addKeyword("function"),
		addKeyword("if"), addKeyword("array"), addKeyword("of"),
		addKeyword("procedure"), addKeyword("program"), addKeyword("record"), addKeyword("then"),
		addKeyword("to"), addKeyword("type"), addKeyword("var"),
		addKeyword("while"), addKeyword("break"), addKeyword("continue"), addKeyword("downto"),
		addKeyword("exit"), addKeyword("repeat"), addKeyword("until");

	addOperation("and"), addOperation("div"), addOperation("mod"),
		addOperation("not"), addOperation("or"), addOperation("xor");

	addOperation("+"), addOperation("-"), addOperation("*"), addOperation("/"),
		addOperation("^"), addOperation("+="), addOperation("-="), addOperation("*="),
		addOperation("/="), addOperation("<"), addOperation(">"), addOperation("<="),
		addOperation(">="), addOperation("="), addOperation("<>"), addOperation(":="),
		addOperation("@"), addOperation(".");

	addSeparator("("), addSeparator(")"), addSeparator("["), addSeparator("]"), addSeparator(";"),
		addSeparator(":"), addSeparator(".."), addSeparator(",");

	addOpChar('+'), addOpChar('-'), addOpChar('*'), addOpChar('^'), addOpChar('/'),
		addOpChar('<'), addOpChar('>'), addOpChar('<'), addOpChar('>'), addOpChar('='),
		addOpChar('<'), addOpChar(':'), addOpChar('@'), addOpChar('.');

	addSepChar('('), addSepChar(')'),
		addSepChar('['), addSepChar(']'),
		addSepChar(';'), addSepChar(':'),
		addSepChar(',');

	strToken["//"] = "singlelineComment";
}

#endif // LEXEM