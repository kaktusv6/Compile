#include "Lexer.h"
#include "Syntax.h"

int main()
{
	Lexer *l = new Lexer();
	Token *t;
	Syntax *s = new Syntax();
	while (!l->getEndFile())
	{
		t = l->nextToken();
		if (t != NULL)
		{
			t->printToken();
			s->takeToken(t);
		}
		if (l->getBuffer() != NULL)
		{
			l->getBuffer()->printToken();
			s->takeToken(l->getBuffer());
			l->setBuffer(NULL);
		}
	}
	return 0;
}