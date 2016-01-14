#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <vector>

using namespace std;

class Node
{
private:
	Token* token;
	vector<Node*> child;

public:
	Node* parent;

	Node(Token* t) : token(t), parent(NULL)
	{ }
	Token* getTokenNode() { return this->token; }
	void addChild(Node* n) { child.push_back(n); }
};

#endif // NODE