
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int amountKeywords = 26;
const int amountOperation = 25;
const int amountSeparators = 8;

static map <string, string> separatorsToken;
static map <string, string> keywordsToken;
static map <string, string> operationToken;

static void addKeyword(string s)
{
	keywordsToken.insert(pair<string, string>(s, "keyword"));
}
static void addOperation(string s)
{
	operationToken.insert(pair<string, string>(s, "op"));
}
static void addSeparators(string s)
{
	separatorsToken.insert(pair<string, string>(s, "sep"));
}
static void addOperationInKeywordMap(string s)
{
	keywordsToken.insert(pair<string, string>(s, "op"));

}
static void initMaps()
{
	addKeyword("begin"),
		addKeyword("forward"),
		addKeyword("do"),
		addKeyword("else"),
		addKeyword("end"),
		addKeyword("for"),
		addKeyword("function"),
		addKeyword("if"),
		addKeyword("array"),
		addKeyword("of"),
		addKeyword("procedure"),
		addKeyword("program"),
		addKeyword("record"),
		addKeyword("then"),
		addKeyword("to"),
		addKeyword("type"),
		addKeyword("var"),
		addKeyword("while"),
		addKeyword("break"),
		addKeyword("continue"),
		addKeyword("downto"),
		addKeyword("exit"),
		addKeyword("repeat"),
		addKeyword("until");

	addOperationInKeywordMap("and"),
		addOperationInKeywordMap("div"),
		addOperationInKeywordMap("mod"),
		addOperationInKeywordMap("not"),
		addOperationInKeywordMap("or"),
		addOperationInKeywordMap("xor");

	addSeparators("+"),
		addSeparators("-"),
		addSeparators("*"),
		addSeparators("/"),
		addSeparators("^"),
		addSeparators("+="),
		addSeparators("-="),
		addSeparators("*="),
		addSeparators("/="),
		addSeparators("<"),
		addSeparators(">"),
		addSeparators("<="),
		addSeparators(">="),
		addSeparators("="),
		addSeparators("<>"),
		addSeparators(":="),
		addSeparators("@"),
		addSeparators(".");
}

class Token
{
private:

public:
	string tokenString;

	Token();
	void checkKeyword(string lexText);
	void checkOperation(string lexText);
	void checkString(string lexText);
};

