#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <vector>

using namespace std;

class Node
{
private:
	Token token;
	vector<Node> child;

public:
	Node(Token t) : token(t)
	{ }

	void addChild(Node n) { child.push_back(n); }
};

#endif // NODE