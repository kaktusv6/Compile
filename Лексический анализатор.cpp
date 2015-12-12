#include <iostream>
#include <fstream>
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