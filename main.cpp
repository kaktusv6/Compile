#include "Lexer.h"
#include "Syntaxer.h"

int main()
{
	Lexer *l = new Lexer();
	Syntaxer *s = new Syntaxer();
	Token *t;
	Node *n;
	while (!l->getEndFile())
	{
		t = l->nextToken();
		if (t != NULL)
		{
			t->printToken();
			n = s->addNodeInTree(t);
		}
		if (l->getBuffer() != NULL)
		{
			l->getBuffer()->printToken();
			n = s->addNodeInTree(l->getBuffer());
			l->setBuffer(NULL);
		}
	}
	return 0;
}