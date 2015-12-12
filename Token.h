
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Token
{
private:

public:
	int lexLine;
	int lexCol;

	string lexText;
	string token;
	Token();
};