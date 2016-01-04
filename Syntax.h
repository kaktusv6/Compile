#pragma once

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

