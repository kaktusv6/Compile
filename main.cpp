#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Lexem.h"

int main()
{
	initMaps();
	Lexer l;
	while (!l.endFile && !fin.eof())
	{
		l.nextLexem();
	}
	return 0;
}