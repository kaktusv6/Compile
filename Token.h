
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int amountKeywords = 26;
const int amountOperation = 25;
const int amountSeparators = 8;

class Token
{
private:
	map <string, string> keywordsToken;
	
	map <string, string> operationToken;

	map <string, string> separatorsToken;
public:
	string tokenString;

	Token();
	void checkKeyword(string lexText);
	void checkOperation(string lexText);
	void checkString(string lexText);
};

