#include "Lexer.h"
#include "Syntax.h"

int main()
{
	Lexer *l = new Lexer();
	Syntax *s = new Syntax();
	Token *t;
	Node *n;
	while (!l->getEndFile())
	{
		t = l->nextToken();
		if (t != NULL)
		{
			t->printToken();
			n = s->takeToken(t);
		}
		if (l->getBuffer() != NULL)
		{
			l->getBuffer()->printToken();
			n = s->takeToken(l->getBuffer());
			l->setBuffer(NULL);
		}
	}
	return 0;
}