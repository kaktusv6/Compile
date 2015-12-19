#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Lexem.h"

int main()
{
	initMaps();
	Lexer *l = new Lexer();
	while (!l->getEndFile() && !fin.eof())
	{
		l->nextToken()->printToken();
	}
	return 0;
}