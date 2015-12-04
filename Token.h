
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

//static map <string, string> separatorsToken;
//static map <string, string> keywordsToken;
//static map <string, string> operationToken;

static vector<char> opCharacter = {'+','-','*','^','/','<','>','<','>','=','<',':','@','.'};

map <string, string> separatorsToken;
map <string, string> keywordsToken;
map <string, string> operationToken;

static void addKeyword(string s)
{
	keywordsToken[s] = "keyword";
}
static void addOperation(string s)
{
	operationToken[s] = "op";
}
static void addSeparators(string s)
{
	separatorsToken[s] = "sep";
}
static void addOperationInKeywordMap(string s)
{
	keywordsToken[s] = "op";
}

static void initMaps()
{
	addKeyword("begin"), addKeyword("forward"), addKeyword("do"), addKeyword("else"), addKeyword("end"), addKeyword("for"), addKeyword("function"), addKeyword("if"), addKeyword("array"), addKeyword("of"), addKeyword("procedure"), addKeyword("program"), addKeyword("record"), addKeyword("then"), addKeyword("to"), addKeyword("type"), addKeyword("var"), addKeyword("while"), addKeyword("break"), addKeyword("continue"), addKeyword("downto"), addKeyword("exit"), addKeyword("repeat"), addKeyword("until");

	addOperationInKeywordMap("and"), addOperationInKeywordMap("div"), addOperationInKeywordMap("mod"), addOperationInKeywordMap("not"), addOperationInKeywordMap("or"), addOperationInKeywordMap("xor");

	addSeparators("+"), addSeparators("-"), addSeparators("*"), addSeparators("/"), addSeparators("^"), addSeparators("+="), addSeparators("-="), addSeparators("*="), addSeparators("/="), addSeparators("<"), addSeparators(">"), addSeparators("<="), addSeparators(">="), addSeparators("="), addSeparators("<>"), addSeparators(":="), addSeparators("@"), addSeparators(".");
}

static bool toOperation(char c)
{
	unsigned i = 0;
	while (i < opCharacter.size() && c != opCharacter[i]) i++;
	if (i < opCharacter.size()) return true;
	else return false;
}

class Token
{
private:

public:
	//static map <string, string> separatorsToken;
	//static map <string, string> keywordsToken;
	//static map <string, string> operationToken;
	string tokenString;
	int f = 0;
	
	Token();
	void checkKeyword(string lexText);
	void checkOperation(string lexText);
	void checkString(string lexText);
};



