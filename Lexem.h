#include<iostream>
#include<map>

using namespace std;

map <string, string> strToken;
vector<char> opChar;
vector<char> sepChar;

void addKeyword(string s)
{
	strToken[s] = "keyword";
}
void addOperation(string s)
{
	strToken[s] = "op";
}
void addSeparators(string s)
{
	strToken[s] = "sep";
}
void addOperationInKeywordMap(string s)
{
	strToken[s] = "op";
}
void addSeparator(string s)
{
	strToken[s] = "sep";
}

void initOpChar()
{
	opChar.push_back('+'), opChar.push_back('-'), opChar.push_back('*'), opChar.push_back('^'), opChar.push_back('/'),
		opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('<'), opChar.push_back('>'), opChar.push_back('='),
		opChar.push_back('<'), opChar.push_back(':'), opChar.push_back('@'), opChar.push_back('.');
}
void initSepChar()
{
	sepChar.push_back('('), sepChar.push_back(')'),
		sepChar.push_back('['), sepChar.push_back(']'),
		sepChar.push_back(';'), sepChar.push_back(':'),
		sepChar.push_back(',');
}
void initMaps()
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

bool toOperation(char c)
{
	unsigned i = 0;
	while (i < opChar.size() && c != opChar[i]) i++;
	if (i < opChar.size()) return true;
	else return false;
}

bool toSep(char c)
{
	unsigned i = 0;
	while (i < sepChar.size() && c != sepChar[i]) i++;
	if (i < sepChar.size()) return true;
	else return false;
}