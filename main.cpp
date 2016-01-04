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
			s->takeToken(t);
			
			t->printToken();
		}
		if (l->getBuffer() != NULL)
		{
			s->takeToken(l->getBuffer());

			l->getBuffer()->printToken();
			l->setBuffer(NULL);
		}
	}
	return 0;
}