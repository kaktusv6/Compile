#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Lexem.h"

int main()
{
	initMaps();
	Lexer *l = new Lexer();
	Token *t;
	while (!l->getEndFile() && !fin.eof())
	{
		t = l->nextToken();
		if (t != NULL) t->printToken();
	}
	return 0;
}