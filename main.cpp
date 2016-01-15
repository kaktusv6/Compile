#include "Parser.h"

int main(int argc, char* argv[])
{
	Lexer *l = new Lexer();
	Parser *p = new Parser(l);
	Token *t;
	Node *n = new Node();
	while (!l->getEndFile())
	{
		n = p->parsAdd();
	}
	return 0;
}