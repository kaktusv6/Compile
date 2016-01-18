#include "Parser.h"

int main(int argc, char* argv[])
{
	Lexer *l = new Lexer();
	Parser *p = new Parser(l);
	Node *n = new Node();

	n = p->parsRelat();
	n->printNode(0);
	system("pause");
	return 0;
}