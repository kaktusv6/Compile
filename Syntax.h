#pragma once

#include "Token.h"
#include "Node.h"

class Syntax
{
private:
	Node *node;
public:
	void takeToken(Token*);
};

