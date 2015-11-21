#pragma once
#include <string>
class Token
{
private:
	enum tokenKeywords { BEGIN, FORWARD, DO, ELSE, END, FOR, FUNCTION, IF, ARRAY, OF, PROCEDURE, PROGRAM, RECORD, THEN, TO, TYPE, VAR, WHILE, BREAK, CONTINUE, DOWNTO, EXIT, REPEAT, UNTIL };
	//string tokenOperation[25] = { "and", "div", "mod", "not", "or", "xor", "+", "-", "*", "/", "^", "+=", "-=", "*=", "/=", "<", ">", "<=", ">=", "=", "<", ">", ":=", "@", "."};
public:
	Token();
	~Token();

};

