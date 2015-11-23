#include "Token.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Token::Token()
{
	keywordsToken.insert(pair<string, string>("begin", "keyword"));
	keywordsToken.insert(pair<string, string>("forward", "keyword"));
	keywordsToken.insert(pair<string, string>("do", "keyword"));
	keywordsToken.insert(pair<string, string>("else", "keyword"));
	keywordsToken.insert(pair<string, string>("end", "keyword"));
	keywordsToken.insert(pair<string, string>("for", "keyword"));
	keywordsToken.insert(pair<string, string>("function", "keyword"));
	keywordsToken.insert(pair<string, string>("if", "keyword"));
	keywordsToken.insert(pair<string, string>("array", "keyword"));
	keywordsToken.insert(pair<string, string>("of", "keyword"));
	keywordsToken.insert(pair<string, string>("procedure", "keyword"));
	keywordsToken.insert(pair<string, string>("program", "keyword"));
	keywordsToken.insert(pair<string, string>("record", "keyword"));
	keywordsToken.insert(pair<string, string>("then", "keyword"));
	keywordsToken.insert(pair<string, string>("to", "keyword"));
	keywordsToken.insert(pair<string, string>("type", "keyword"));
	keywordsToken.insert(pair<string, string>("var", "keyword"));
	keywordsToken.insert(pair<string, string>("while", "keyword"));
	keywordsToken.insert(pair<string, string>("break", "keyword"));
	keywordsToken.insert(pair<string, string>("continue", "keyword"));
	keywordsToken.insert(pair<string, string>("downto", "keyword"));
	keywordsToken.insert(pair<string, string>("exit", "keyword"));
	keywordsToken.insert(pair<string, string>("repeat", "keyword"));
	keywordsToken.insert(pair<string, string>("until", "keyword"));

	keywordsToken.insert(pair<string, string>("and", "op"));
	keywordsToken.insert(pair<string, string>("div", "op"));
	keywordsToken.insert(pair<string, string>("mod", "op"));
	keywordsToken.insert(pair<string, string>("not", "op"));
	keywordsToken.insert(pair<string, string>("or", "op"));
	keywordsToken.insert(pair<string, string>("xor", "op"));
	
	operationToken.insert(pair<string, string>("+", "op"));
	operationToken.insert(pair<string, string>("-", "op"));
	operationToken.insert(pair<string, string>("*", "op"));
	operationToken.insert(pair<string, string>("/", "op"));
	operationToken.insert(pair<string, string>("^", "op"));
	operationToken.insert(pair<string, string>("+=", "op"));
	operationToken.insert(pair<string, string>("-=", "op"));
	operationToken.insert(pair<string, string>("*=", "op"));
	operationToken.insert(pair<string, string>("/=", "op"));
	operationToken.insert(pair<string, string>("<", "op"));
	operationToken.insert(pair<string, string>(">", "op"));
	operationToken.insert(pair<string, string>("<=", "op"));
	operationToken.insert(pair<string, string>(">=", "op"));
	operationToken.insert(pair<string, string>("=", "op"));
	operationToken.insert(pair<string, string>("<>", "op"));
	operationToken.insert(pair<string, string>(":=", "op"));
	operationToken.insert(pair<string, string>("@", "op"));
	operationToken.insert(pair<string, string>(".", "op"));


}

void Token::checkKeyword(string lexText)
{
	map<string, string>::iterator i = keywordsToken.find(lexText);
	if (i != keywordsToken.end()) tokenString = i->second;
	else tokenString = "ident";
}

void Token::checkOperation(string lexText)
{
	map<string, string>::iterator i = operationToken.find(lexText);
	if (i != operationToken.end()) tokenString = i->second;
	else tokenString = "BadChar";
}

//Token::Token()
//{
//	keywordsMap["begin"] = BEGIN;
//	keywordsMap["forward"] = FORWARD;
//	keywordsMap["do"] = DO;
//	keywordsMap["else"] = ELSE;
//	keywordsMap["end"] = END;
//	keywordsMap["for"] = FOR;
//	keywordsMap["function"] = FUNCTION;
//	keywordsMap["if"] = IF;
//	keywordsMap["array"] = ARRAY;
//	keywordsMap["of"] = OF;
//	keywordsMap["procedure"] = PROCEDURE;
//	keywordsMap["program"] = PROGRAM;
//	keywordsMap["record"] = RECORD;
//	keywordsMap["then"] = THEN;
//	keywordsMap["to"] = TO;
//	keywordsMap["type"] = TYPE;
//	keywordsMap["var"] = VAR;
//	keywordsMap["while"] = WHILE;
//	keywordsMap["break"] = BREAK;
//	keywordsMap["continue"] = CONTINUE;
//	keywordsMap["downto"] = DOWNTO;
//	keywordsMap["exit"] = EXIT;
//	keywordsMap["repeat"] = REPEAT;
//	keywordsMap["until"] = UNTIL;
//}

//void Token::lexemToToken(string s)
//{
//	map<string, token>::iterator i = keywordsMap.find(s);
//	if (i == keywordsMap.end())
//	{
//		tok = ID;
//	}
//	else tok = i->second;
//}

//string Token::tokenToString()
//{
//	switch (tok)
//	{
//		case ID : return "id"; break;
//		case OP : return "op"; break;
//		case BEGIN : return "begin"; break;
//		case FORWARD : return "forward"; break;
//		case DO : return "do"; break;
//		case ELSE : return "else"; break;
//		case END : return "end"; break;
//		case FOR : return "for"; break;
//		case FUNCTION : return "function"; break;
//		case IF : return "if"; break;
//		case ARRAY : return "array"; break;
//		case OF : return "of"; break;
//		case PROCEDURE : return "procedure"; break;
//		case PROGRAM : return "program"; break;
//		case RECORD : return "record"; break;
//		case THEN : return "then"; break;
//		case TO : return "to"; break;
//		case TYPE : return "type"; break;
//		case VAR : return "var"; break;
//		case WHILE : return "while"; break;
//		case BREAK : return "break"; break;
//		case CONTINUE : return "continue"; break;
//		case DOWNTO : return "downto"; break;
//		case EXIT : return "exit"; break;
//		case REPEAT : return "repeat"; break;
//		case UNTIL : return "until"; break;
//		default: return "error";
//	}
//}

