#include "Lexer.h"

int main()
{
	Lexer *l = new Lexer();
	Token *t;
	while (!l->getEndFile())
	{
		t = l->nextToken();
		if (t != NULL) { t->printToken(); }
	}
	return 0;
}