
#include "Node.h"

class Syntax
{
private:
	Node* currentNode;
public:
	Syntax() : currentNode(NULL)
	{}
	Node takeToken(Token*);
};

