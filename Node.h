#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <vector>
#include <iostream>

using namespace std;

class Node
{
private:
	Token* token;
	vector<Node*> childs;
public:
	Node* parent;

	Node() : parent(NULL)
	{  }
	Node(Token* t) : token(t), parent(NULL)
	{ }

	//Token* getTokenNode() { return this->token; } Пока ни где не применяется

	void addChild(Node* n)
	{
		n->parent = this;
		childs.push_back(n);
	}
	void printNode(int i)
	{
		int a = i;
		while (a > 0)
		{
			cout << "  ";
			a--;
		}
		cout << this->token->getLexText() << endl;
		int j = childs.size();
		while (j > 0)
		{
			if (childs[j-1] != NULL)
			{ childs[j-1]->printNode(i + 1); }
			j--;
		}
	}
};

#endif // NODE