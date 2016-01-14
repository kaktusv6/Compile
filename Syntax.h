#ifndef SYNTAX_H
#define SYNTAX_H

#include "Token.h"
#include "Node.h"

class Syntax
{
private:
	Node *node;
public:
	Syntax();
	void takeToken(Token*);
};

#endif // TOKEN