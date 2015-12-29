#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>

using namespace std;

class Node
{
private:
	Token expression;
	Node *rightChild;
	Node *leftChild;
public:
	Node();
};

#endif // NODE