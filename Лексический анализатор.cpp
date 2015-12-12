#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "Lexem.h"
#include "Token.h"
#include "Lexer.h"

int main()
{
	initMaps();
	Lexer l;
	while (l.endFile && !fin.eof())
	{
		l.nextLexem();
	}
	return 0;
}